//抽象类
class IDBConnection {
};

class IDBCommand {
};

class IDBReader {
};

class IDBAbstractFactory {
public:
    virtual IDBConnection *createDBConnection() = 0;
    virtual IDBCommand *createDBCommand() = 0;
    virtual IDBReader *createDBReader() = 0;
};

//具体类
//1. SQL Server的
class SQLDBConnection : public IDBConnection {
};

class SQLDBCommand : public IDBCommand {
};

class SQLDBReader : public IDBReader {
};

class SQLDBAbstractFactory : public IDBAbstractFactory{
public:
    IDBConnection *createDBConnection() override {
        return new SQLDBConnection();
    }

    IDBCommand *createDBCommand() override {
        return new SQLDBCommand();
    }

    IDBReader *createDBReader() override {
        return new SQLDBReader();
    }
};

//2.支持MySQL的....（省略）
//3.支持Oracle的....（省略）

//使用
class EmployeeDAO{
public:
    void getEmployee(){
        IDBConnection *iConn = idf->createDBConnection();
        IDBCommand *iCmd = idf->createDBCommand();
        IDBReader *iRd = idf->createDBReader();
        /* do something */
    }


private:
    IDBAbstractFactory *idf;
};