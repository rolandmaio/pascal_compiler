#ifndef GOTO
#define GOTO

class Goto {
    public:
        Goto(size_t hole) : hole(hole){}
        size_t getHole(){ return hole; }
    private:
        size_t hole;
};

#endif
