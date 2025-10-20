//
// Created by Magnitola on 17.10.2025.
//

#pragma once
#include <fstream>
#include <iosfwd>
#include <typeindex>


class FieldInfo;
class TypeInfo;

class Serializer {
public:
    static void serialize(void *object, const TypeInfo &info);

private:
    static void serializeType(void *object, const TypeInfo &info, std::ofstream &file, int level);

    static void serializeField(void *object, const FieldInfo &field, std::ofstream &file, int level);

    static void serializeVector(void *object, const FieldInfo &field, std::ofstream &file, int level);

    static std::string tab(int level);

    static std::string valueToString(const void *value, std::type_index type);
};
