#include "../token.h"

class Node {
    public:
        virtual ~Node() = default; //Virtual destructor
        //"Destructor will be called for any object that is derived from the class, even if the object is deleted through a pointer to the base class"
};
