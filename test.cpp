#include "pch.h"
#include "../dictionary/dictionary.cpp"
#include "../dictionary/dictionary.h"

TEST(dict_test, punctuation_test)
{
	EXPECT_EQ(true, checkPunctuationMark(true));	
}



TEST(dict_test, lower_case_test)
{
	EXPECT_EQ(true, checkLowerCase(true));	
}

TEST(dict_test, final_output_test)
{
	EXPECT_EQ(true, checkFinal(true));	
}
