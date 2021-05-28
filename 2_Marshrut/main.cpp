#include <UnitTest++/UnitTest++.h>
#include "/home/student/timp_labwork_3/2_Marshrut/modMarshCipher.h"
#include "/home/student/timp_labwork_3/2_Marshrut/modMarshCipher.cpp"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("LLEHO",modMarshCipher("4").encrypt("HELLO"));
    }
    TEST(LetterInKey) {
        CHECK_THROW(modMarshCipher cp("Б1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modMarshCipher cp("1,1"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modMarshCipher cp("1 2"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modMarshCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modMarshCipher cp("1"),cipher_error);
    }
}

struct KeyB_fixture {
    modMarshCipher * p;
    KeyB_fixture()
    {
        p = new modMarshCipher("4");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("LRLOEWDHOL",
                    p->encrypt("HELLOWORLD"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("LRLOEWDHOL",
                    p->encrypt("helloworld"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("LRLOEWDHOL",
                    p->encrypt("HELLO WORLD!!!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("LRLOEWDHOL", p->encrypt("HELLO 2021 WORLD"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("1234+8765=9999"),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("DLROWOLLEH",
                    modMarshCipher("10").encrypt("HELLOWORLD"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("HELLOWORLD",
                    p->decrypt("LRLOEWDHOL"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("lrloeWDHOL"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("LRLOE WDHOL"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("LRLOE2021WDHOL"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("LRLOE,WDHOL"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("HELLOWORLD",
                    modMarshCipher("10").decrypt("DLROWOLLEH"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
