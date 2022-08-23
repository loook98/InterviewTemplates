//抽象类
class ISpliter {
public:
    virtual void split()=0;
    virtual ~ISpliter(){}
};
class ISpliterFactory {
public:
    virtual ISpliter *createSpliter() = 0;
    virtual ~ISpliterFactory(){}
};

//具体类。一种Spliter对应一个Factory
//1.文本文件分割器
class TxtSpliter : public ISpliter {
public:
    void split() override {
    }
};
class TxtSpliterFactory : public ISpliterFactory {
public:
    ISpliter *createSpliter() override {
       return new TxtSpliter();
    }
};

//2. 二进制文件分割器....（省略）
//3. ......

//使用
class MainForm{
public:
    MainForm(ISpliterFactory *iFactory):isf(iFactory){}

    void foo(){
        ISpliter *is = isf->createSpliter();
    }
private:
    ISpliterFactory *isf;
};


