//
// Created by Magnitola on 18.10.2025.
//

#pragma once
#include <fstream>

#include "reflection/Reflector.h"

class Deserializer {
public:
    static void deserialize(void *object, const TypeInfo &info);

private:
    static void deserializeFromLines(int &currentIndex, const std::vector<std::string> &lines,
                                     int currentLevel, void *object, const TypeInfo &info);

    static void deserializeVector(int &currentIndex, const std::vector<std::string> &lines,
                                  int currentLevel, void *object, const FieldInfo &field);

    static int countTabs(const std::string &line);

    static std::pair<std::string, std::string> splitString(const std::string& input);

    static std::any parseStringToValue(const std::string& value, const std::type_index& type);
    static void setPrimitiveValue(void* object, const FieldInfo& field, const std::string& value);
    static void setVectorElementValue(void* element, const FieldInfo& field, const std::string& value);
};
