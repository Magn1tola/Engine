//
// Created by Magnitola on 17.10.2025.
//

#include "Serializer.h"

#include "reflection/Reflector.h"

void Serializer::serialize(void *object, const TypeInfo &info) {
    std::ofstream file(info.getClassName() + ".stype");
    serializeType(object, info, file, 0);
    file.close();
}

void Serializer::serializeType(void *object, const TypeInfo &info, std::ofstream &file, int level) {
    file << "type:" << std::endl;
    for (const auto &[name, field]: info.getAllFields()) {
        serializeField(object, field, file, level + 1);
    }
}

void Serializer::serializeField(void *object, const FieldInfo &field, std::ofstream &file, int level) {
    file << tab(level) << field.getName() << ": ";

    if (field.isVector()) {
        serializeVector(object, field, file, level + 1);
    } else if (const auto type = Reflector::getTypeInfo(field.getTypeIndex().name()); type != nullptr) {
        serializeType(field.getValue(object), *type, file, level);
    } else {
        file << valueToString(field.getValue(object), field.getTypeIndex()) << std::endl;
    }
}

void Serializer::serializeVector(void *object, const FieldInfo &field, std::ofstream &file, int level) {
    file << "vector:" << std::endl;

    const size_t size = field.getVectorSize(object);
    file << tab(level) << "size: " << size << std::endl;
    file << tab(level) << "elementType: " << field.getElementTypeIndex().name() << std::endl;
    file << tab(level) << "elements:" << std::endl;

    for (size_t i = 0; i < size; i++) {
        void *element = field.getVectorElement(object, i);
        if (element != nullptr) {
            file << tab(level + 1) << i << ": ";

            if (const auto elementType = Reflector::getTypeInfo(field.getElementTypeIndex().name());
                elementType != nullptr) {
                serializeType(element, *elementType, file, level + 1);
            } else {
                file << valueToString(element, field.getElementTypeIndex()) << std::endl;
            }
        }
    }
}

std::string Serializer::tab(const int level) {
    return std::string(level, '\t');
}

std::string Serializer::valueToString(const void *value, const std::type_index type) {
    if (type == typeid(bool)) {
        return std::to_string(*static_cast<const bool *>(value));
    } else if (type == typeid(int)) {
        return std::to_string(*static_cast<const int *>(value));
    } else if (type == typeid(float)) {
        return std::to_string(*static_cast<const float *>(value));
    } else if (type == typeid(double)) {
        return std::to_string(*static_cast<const double *>(value));
    } else if (type == typeid(std::string)) {
        return *static_cast<const std::string *>(value);
    }
    return "";
}
