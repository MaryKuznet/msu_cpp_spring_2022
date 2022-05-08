#include "format.cpp"
#include <gtest/gtest.h>

class TestFormat : public ::testing::Test{
    protected:
	void SetUp(){}
	void TearDown(){}
};

// Проверяем, основную работу функции
TEST_F(TestFormat, Test1){
    std::string a = "abc 12";
    ASSERT_EQ(a, format("abc {0}", 12));

    std::string b = "abc 3 and 12";
    ASSERT_EQ(b, format("abc {1} and {0}", 12, 3));

    std::string c = "abc 3 and wait";
    std::string d = "wait";
    ASSERT_EQ(c, format("abc {1} and {0}", d, 3));

    std::string e = "abc 3 and wait, good, wait";
    ASSERT_EQ(e, format("abc {1} and {0}, {2}, {0}", d, 3, "good"));

    std::string g = "abc";
    ASSERT_EQ(g, format("abc", 12, 3));

    std::string k = "abc";
    ASSERT_EQ(k, format("abc"));
}

// Проверяем, что выбрасывается наше исключение
TEST_F(TestFormat, Test2)
{
    ASSERT_THROW(format("abc {}"), MyError);
    ASSERT_THROW(format("abc {0}"), MyError);
    ASSERT_THROW(format("abc {1}", 1), MyError);
    ASSERT_THROW(format("abc {d}", 1), MyError);
    ASSERT_THROW(format("abc {", 1), MyError);
    ASSERT_THROW(format("abc {123", 1), MyError);
    ASSERT_THROW(format("abc dbf} fgh", 1), MyError);
}

// Проверяем, что выбрасывается исключение с правильным типом
TEST_F(TestFormat, Test3){
    try{
        format("abc {}");
    }
    catch (MyError e){
        ASSERT_EQ(e.error_type, ExceptionType::Not_number);
    };

    try{
        format("abc {0}");
    }
    catch (MyError e){
        ASSERT_EQ(e.error_type, ExceptionType::Not_enough_args);
    };

    try{
        format("abc {d}");
    }
    catch (MyError e){
        ASSERT_EQ(e.error_type, ExceptionType::Bad_number);
    };

    try{
        format("abc {");
    }
    catch (MyError e){
        ASSERT_EQ(e.error_type, ExceptionType::Not_number);
    };

    try{
        format("abc {123", 1);
    }
    catch (MyError e){
        ASSERT_EQ(e.error_type, ExceptionType::Bad_number);
    };

    try{
        format("abc dbf} fgh", 1);
    }
    catch (MyError e){
        ASSERT_EQ(e.error_type, ExceptionType::Only_one_bracket);
    };
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
