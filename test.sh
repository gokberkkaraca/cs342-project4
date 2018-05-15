javac number_generator.java
echo

echo "test1";
java NumberGenerator 100 200 > test1.txt
./ds 500 test1.txt

echo
echo "test2";
java NumberGenerator 100 400 > test2.txt
./ds 500 test2.txt

echo
echo "test3";
java NumberGenerator 100 600 > test3.txt
./ds 500 test3.txt

echo
echo "test4";
java NumberGenerator 100 800 > test4.txt
./ds 500 test4.txt

echo
echo "test5";
java NumberGenerator 100 1000 > test5.txt
./ds 500 test5.txt

echo
echo "test6";
java NumberGenerator 200 200 > test6.txt
./ds 500 test6.txt

echo
echo "test7";
java NumberGenerator 200 400 > test7.txt
./ds 500 test7.txt

echo
echo "test8";
java NumberGenerator 200 600 > test8.txt
./ds 500 test8.txt

echo
echo "test9";
java NumberGenerator 200 800 > test9.txt
./ds 500 test9.txt
echo

echo "test10";
java NumberGenerator 200 1000 > test10.txt
./ds 500 test10.txt
echo

echo "test11";
java NumberGenerator 300 200 > test11.txt
./ds 500 test11.txt
echo

echo "test12";
java NumberGenerator 300 400 > test12.txt
./ds 500 test12.txt
echo

echo "test13";
java NumberGenerator 300 600 > test13.txt
./ds 500 test13.txt
echo

echo "test14";
java NumberGenerator 300 800 > test14.txt
./ds 500 test14.txt
echo

echo "test15";
java NumberGenerator 300 1000 > test15.txt
./ds 500 test15.txt
echo

echo "test16";
java NumberGenerator 400 200 > test16.txt
./ds 500 test16.txt
echo

echo "test17";
java NumberGenerator 400 400 > test17.txt
./ds 500 test17.txt
echo

echo "test18";
java NumberGenerator 400 600 > test18.txt
./ds 500 test18.txt
echo

echo "test19";
java NumberGenerator 400 800 > test19.txt
./ds 500 test19.txt
echo

echo "test20";
java NumberGenerator 400 1000 > test20.txt
./ds 500 test20.txt
echo

echo "test21";
java NumberGenerator 500 200 > test21.txt
./ds 500 test21.txt
echo

echo "test22";
java NumberGenerator 500 400 > test22.txt
./ds 500 test22.txt
echo

echo "test23";
java NumberGenerator 500 600 > test23.txt
./ds 500 test23.txt
echo

echo "test24";
java NumberGenerator 500 800 > test24.txt
./ds 500 test24.txt
echo

echo "test25";
java NumberGenerator 500 1000 > test25.txt
./ds 500 test25.txt

rm test*.txt;
rm NumberGenerator.class
