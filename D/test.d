
import std.conv : emplace;
import core.stdc.stdlib;

B heapAllocate(B, Args...) (Args args) 
{
    import std.conv : emplace;
    import core.stdc.stdlib : malloc;
    import core.memory : GC;
    
    // get class size of class instance in bytes
    auto size = __traits(classInstanceSize, T);
    
    // allocate memory for the object
    auto memory = malloc(size)[0..size];
    if(!memory)
    {
        import core.exception : onOutOfMemoryError;
        onOutOfMemoryError();
    }                    
    
    writeln("Memory allocated");

    // notify garbage collector that it should scan this memory
    GC.addRange(memory.ptr, size);
    
    // call T's constructor and emplace instance on
    // newly allocated memory
    return emplace!(B, Args)(memory, args);                                    
}

class A{
    this(int a){
        this.a = a;
    }
    B createB(int b){
        B ptr = cast(B)malloc(B.sizeof);
        return emplace!(B, int)(ptr, a);
    }
    int a;
}

class B : A{
    this(int a, int b){
        super(a);
        this.b = b;
    }
    int b;
}

int main(){
    A a = new A(1);
    B b2 = a.createB(2);
    B b = new B(1, 2);
    return 0;
}

