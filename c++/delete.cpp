
void delete_func() {}

class test {
    public:
        test() {}
        ~test(){return delete_func();}
};
