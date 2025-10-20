//
// Created by Magnitola on 18.10.2025.
//

#include "Deserializer.h"

#include <iostream>
#include <ranges>

#include "log/Log.h"

void Deserializer::deserialize(void *object, const TypeInfo &info) {
    const auto fileName = info.getClassName() + ".stype";
    std::ifstream file(fileName);
    if (!file.is_open()) {
        LOGE("Failed to open file {}", fileName);
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(std::move(line));
    }
    file.close();

    if (lines.empty()) {
        LOGE("Empty file: {}", fileName);
        return;
    }

    int currentIndex = 1;
    deserializeFromLines(currentIndex, lines, 1, object, info);
}

void Deserializer::deserializeFromLines(int &currentIndex, const std::vector<std::string> &lines, int currentLevel,
                                        void *object, const TypeInfo &info) {
    while (currentIndex < lines.size()) {
        const std::string &line = lines[currentIndex];
        const int lineLevel = countTabs(line);

        if (lineLevel < currentLevel) return;
        if (lineLevel > currentLevel) {
            LOGE("Unexpected level in field metadata: {}", line);
            currentIndex++;
            continue;
        }

        auto [key, value] = splitString(line);
        if (const auto field = info.getField(key); field != nullptr) {
            try {
                if (value == "type:") {
                    if (const auto newType = Reflector::getTypeInfo(field->getTypeIndex().name()); newType != nullptr) {
                        const auto newObject = field->getValue(object);
                        deserializeFromLines(++currentIndex, lines, currentLevel + 1, newObject, *newType);
                    }
                } else if (value == "vector:") {
                    if (field->isVector()) {
                        deserializeVector(++currentIndex, lines, currentLevel + 1, object, *field);
                    }
                } else {
                    setPrimitiveValue(object, *field, value);
                    currentIndex++;
                }
            } catch (const std::exception &e) {
                LOGE("Deserialize error: {} in line {}", e.what(), line);
                currentIndex++;
            }
        } else {
            currentIndex++;
        }
    }
}

void Deserializer::deserializeVector(int &currentIndex, const std::vector<std::string> &lines, int currentLevel,
                                     void *object, const FieldInfo &field) {
    size_t size = 0;
    std::string elementTypeName;
    bool foundElements = false;

    while (currentIndex < lines.size()) {
        const std::string &line = lines[currentIndex];
        const int lineLevel = countTabs(line);

        if (lineLevel < currentLevel) break;
        if (lineLevel > currentLevel) {
            LOGE("Unexpected level in vector metadata: {}", line);
            currentIndex++;
            continue;
        }

        auto [key, value] = splitString(line);

        if (key == "size") {
            size = std::stoul(value);
        } else if (key == "elementType") {
            elementTypeName = value;
        } else if (key == "elements:") {
            foundElements = true;
            currentIndex++;
            break;
        }
        currentIndex++;
    }

    if (!foundElements || size == 0) {
        LOGE("Invalid vector format or empty vector");
        return;
    }

    field.setVectorSize(object, size);

    for (size_t i = 0; i < size && currentIndex < lines.size(); i++) {
        const std::string &line = lines[currentIndex];
        const int lineLevel = countTabs(line);

        if (lineLevel < currentLevel) break;
        if (lineLevel != currentLevel + 1) {
            LOGE("Unexpected level for vector element: {}", line);
            currentIndex++;
            continue;
        }

        auto [indexStr, value] = splitString(line);

        try {
            const size_t index = std::stoul(indexStr);
            if (index != i) {
                LOGE("Vector element index mismatch: expected {}, got {}", i, index);
            }

            void *element = field.getVectorElement(object, index);
            if (element != nullptr) {
                if (value == "type:") {
                    if (const auto elementType = Reflector::getTypeInfo(elementTypeName); elementType != nullptr) {
                        deserializeFromLines(++currentIndex, lines, lineLevel + 1, element, *elementType);
                    }
                } else {
                    setVectorElementValue(element, field, value);
                    currentIndex++;
                }
            }
        } catch (const std::exception &e) {
            LOGE("Deserialize error: {} in line {}", e.what(), line);
            currentIndex++;
        }
    }
}

int Deserializer::countTabs(const std::string &line) {
    int count = 0;
    for (const char c: line) {
        if (c == '\t') count++;
        else break;
    }
    return count;
}

std::pair<std::string, std::string> Deserializer::splitString(const std::string &input) {
    size_t start = input.find_first_not_of('\t');
    if (start == std::string::npos) start = 0;

    size_t delimiter_pos = input.find(": ", start);

    if (delimiter_pos != std::string::npos) {
        std::string key = input.substr(start, delimiter_pos - start);
        std::string value = input.substr(delimiter_pos + 2);
        return {key, value};
    }

    return {input.substr(start), ""};
}

void Deserializer::setPrimitiveValue(void *object, const FieldInfo &field, const std::string &value) {
    const auto type = field.getTypeIndex();
    auto parsedValue = parseStringToValue(value, type);
    if (parsedValue.has_value()) {
        field.setValue(object, parsedValue);
    } else {
        LOGE("Unsupported field type: {}", type.name());
    }
}

void Deserializer::setVectorElementValue(void *element, const FieldInfo &field, const std::string &value) {
    const auto &elementType = field.getElementTypeIndex();
    auto parsedValue = parseStringToValue(value, elementType);

    if (parsedValue.has_value()) {
        if (elementType == typeid(bool)) {
            *static_cast<bool *>(element) = std::any_cast<bool>(parsedValue);
        } else if (elementType == typeid(int)) {
            *static_cast<int *>(element) = std::any_cast<int>(parsedValue);
        } else if (elementType == typeid(float)) {
            *static_cast<float *>(element) = std::any_cast<float>(parsedValue);
        } else if (elementType == typeid(double)) {
            *static_cast<double *>(element) = std::any_cast<double>(parsedValue);
        } else if (elementType == typeid(std::string)) {
            *static_cast<std::string *>(element) = std::any_cast<std::string>(parsedValue);
        }
    } else {
        LOGE("Unsupported vector element type: {}", elementType.name());
    }
}

std::any Deserializer::parseStringToValue(const std::string &value, const std::type_index &type) {
    if (type == typeid(bool)) {
        return static_cast<bool>(std::stoi(value));
    } else if (type == typeid(int)) {
        return std::stoi(value);
    } else if (type == typeid(float)) {
        return std::stof(value);
    } else if (type == typeid(double)) {
        return std::stod(value);
    } else if (type == typeid(std::string)) {
        return value;
    }
    return {};
}
