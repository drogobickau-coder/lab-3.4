#include "pch.h"
#include "CppUnitTest.h"

#include "../lab_3.4#/SymString.h"
#include "../lab_3.4#/DecString.h"
#include "../lab_3.4#/Factory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab34UnitTest
{
    TEST_CLASS(Lab34UnitTest)
    {
    public:
        
        TEST_METHOD(TestSymStringAddition)
        {
            SymString s1("s1", "Hello, ");
            SymString s2("s2", "OOP!");

            SymString res = s1 + s2;

            Assert::AreEqual(std::string("s1+s2"), res.getId());
            Assert::AreEqual(std::string("Hello, OOP!"), res.getValue());
        }

      
        TEST_METHOD(TestSymStringSetIdValidation)
        {
            SymString s("id1", "test");

            Assert::IsFalse(s.setId(""));
            Assert::AreEqual(std::string("id1"), s.getId());

            Assert::IsTrue(s.setId("id2"));
            Assert::AreEqual(std::string("id2"), s.getId());
        }

       
        TEST_METHOD(TestDecStringValidation)
        {
            Assert::IsTrue(DecString::isValidDec("0"));
            Assert::IsTrue(DecString::isValidDec("12345"));
            Assert::IsFalse(DecString::isValidDec(""));
            Assert::IsFalse(DecString::isValidDec("-10"));
            Assert::IsFalse(DecString::isValidDec("12a4"));

          
            DecString invalid("d_bad", "abc");
            Assert::AreEqual(std::string("0"), invalid.getValue());

          
            DecString normalized("d_norm", "00255");
            Assert::AreEqual(std::string("255"), normalized.getValue());
        }

       
        TEST_METHOD(TestDecStringToHex)
        {
            DecString d1("d1", "255");
            DecString d2("d2", "4095");
            DecString d3("d3", "0");

            Assert::AreEqual(std::string("FF"), d1.toHex());
            Assert::AreEqual(std::string("FFF"), d2.toHex());
            Assert::AreEqual(std::string("0"), d3.toHex());
        }

        
        TEST_METHOD(TestDecStringAddition)
        {
            DecString d1("d1", "255");
            DecString d2("d2", "45");

            DecString res = d1 + d2;

            Assert::AreEqual(std::string("d1+d2"), res.getId());
            Assert::AreEqual(std::string("300"), res.getValue());
            Assert::AreEqual(std::string("12C"), res.toHex());
        }

        
        TEST_METHOD(TestFactoryOperations)
        {
            Factory factory;

            // Створення коректних об'єктів
            SymString* s = factory.createSymString("s1", "text");
            DecString* d = factory.createDecString("d1", "16");
            Assert::IsNotNull(s);
            Assert::IsNotNull(d);
            Assert::AreEqual(std::string("10"), d->toHex());

            // Заборона дублювання ID та некоректних значень
            Assert::IsNull(factory.createSymString("s1", "duplicate"));
            Assert::IsNull(factory.createDecString("d2", "12x"));

            // Видалення і перевірка, що об'єкти зникли
            Assert::IsTrue(factory.deleteSymString("s1"));
            Assert::IsNull(factory.findSymString("s1"));
            Assert::IsFalse(factory.deleteSymString("s1"));

            Assert::IsTrue(factory.deleteDecString("d1"));
            Assert::IsNull(factory.findDecString("d1"));
        }
    };
}