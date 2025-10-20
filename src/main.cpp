#define GLEW_STATIC

#include <vector>

#include "Application.h"
#include "reflection/Reflector.h"
#include "serialization/Deserializer.h"
#include "serialization/Serializer.h"


class MyVectorClass {
public:
    std::vector<int> numbers;
    std::vector<std::string> names;
    std::vector<float> values;

    BEGIN_REFLECTED_TYPE(MyVectorClass)
        FIELD(numbers)
        FIELD(names)
        FIELD(values)
    END_REFLECTED_TYPE();
};

class MyClass {
public:
    std::string name;
    std::vector<MyVectorClass> fields;

    BEGIN_REFLECTED_TYPE(MyClass)
        FIELD(name)
        FIELD(fields)
    END_REFLECTED_TYPE();
};

int main() {
    Application app{};
    if (!app.initialization()) {
        return -1;
    }

    auto test1 = MyVectorClass{
        {1, 2, 3, 4, 5},
        {"one", "two", "three", "four"},
        {1, 2, 3, 4, 5}
    };

    auto test2 = MyVectorClass{
        {10, 9, 8, 7, 6},
        {"Steeve", "Mark", "Alex", "Bill", "Peter"},
        {10, 9, 8, 7, 6}
    };

    auto my = MyClass{
        "Lada lovers",
        {test1, test2}
    };

    const auto type = MyClass::getTypeInfo();

    Serializer::serialize(&my, *type);

    auto my2 = MyClass{};
    Deserializer::deserialize(&my2, *type);

    app.loop();
    return 0;
}
