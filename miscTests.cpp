#include "gtest/gtest.h"

#include "misc/misc.h"

TEST(multiply, thirdGrade)
{
	EXPECT_STREQ("7006652", ThirdGradeMultiply("5678", "1234").c_str());
}
