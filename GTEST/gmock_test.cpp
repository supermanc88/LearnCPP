#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


// 1. 外部依赖的接口
class Database {
public:
    virtual ~Database() = default;
    virtual bool Connect(const std::string& url) = 0;
    virtual int GetUserAge(const std::string& username) = 0;
};


// 2. 我们需要测试的目标类
class UserService {
    Database* db_;
public:
    // 通过依赖注入传入 Database
    UserService(Database* db) : db_(db) {}

    bool IsAdult(const std::string& username) {
        int age = db_->GetUserAge(username);
        return age >= 18;
    }
};


// 创建 Mock 类
class MockDatabase : public Database {
public:
    // MOCK_METHOD(返回类型, 方法名, (参数列表), (修饰符));
    MOCK_METHOD(bool, Connect, (const std::string& url), (override));
    MOCK_METHOD(int, GetUserAge, (const std::string& username), (override));
};


TEST(UserServiceTest, CheckIfUserIsAdult) {
    // 1. 实例化 Mock 对象
    MockDatabase mock_db;

    // 2. 将 Mock 对象注入到被测类中
    UserService service(&mock_db);

    // 3. 设置期望 (Expectations)
    // 期望：GetUserAge 被调用，参数精确匹配 "Alice"
    // 行为：被调用 1 次，并且返回 20
    EXPECT_CALL(mock_db, GetUserAge("Alice"))
        .Times(1)
        .WillOnce(testing::Return(20));

    // 4. 执行测试：因为设定了返回 20，20 >= 18，所以应该返回 true
    EXPECT_TRUE(service.IsAdult("Alice"));
}



