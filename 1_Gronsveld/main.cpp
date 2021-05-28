#include <UnitTest++/UnitTest++.h>
#include "/home/student/timp_labwork_3/1_Gronsveld/modAlphaCipher.h"
#include "/home/student/timp_labwork_3/1_Gronsveld/modAlphaCipher.cpp"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("БВГБВ",modAlphaCipher("БВГ").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("БВГДЕ",modAlphaCipher("БВГДЕЁЖЗИЙ").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("БВГБВ",modAlphaCipher("бвг").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("Б1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("Б,В"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("Б В"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ВЬТУСБАВФСБАМЙТБ",
                    p->encrypt("БЫСТРАЯБУРАЯЛИСА"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("ВЬТУСБАВФСБАМЙТБ",
                    p->encrypt("быстраябураялиса"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("ВЬТУСБАВФСБАМЙТБ",
                    p->encrypt("БЫСТРАЯ БУРАЯ ЛИСА!!!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("ОПГЬКДПЕ", p->encrypt("Новый 2021 Год"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("1234+8765=9999"),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("АЪРСПЯЮАТПЯЮКЗРЯ",
                    modAlphaCipher("Я").encrypt("БЫСТРАЯ БУРАЯ ЛИСА"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("БЫСТРАЯБУРАЯЛИСА",
                    p->decrypt("ВЬТУСБАВФСБАМЙТБ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("вьтусбаВФСБАМЙТБ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("ВЬТУСБА ВФСБА МЙТБ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("ОПГЬК2021ДПЕ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("ОПГЬ,КДПЕ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("БЫСТРАЯБУРАЯЛИСА",
                    modAlphaCipher("Я").decrypt("АЪРСПЯЮАТПЯЮКЗРЯ"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
