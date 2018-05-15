make
javac number_generator.java
echo

echo "test1";
java NumberGenerator 1000 200 > test1.txt
./ds 1000 test1.txt

echo
echo "test2";
java NumberGenerator 1000 400 > test2.txt
./ds 1000 test2.txt

echo
echo "test3";
java NumberGenerator 1000 600 > test3.txt
./ds 1000 test3.txt

echo
echo "test4";
java NumberGenerator 2000 200 > test4.txt
./ds 1000 test4.txt

echo
echo "test5";
java NumberGenerator 2000 400 > test5.txt
./ds 1000 test5.txt

echo
echo "test6";
java NumberGenerator 2000 600 > test6.txt
./ds 1000 test6.txt

echo
echo "test7";
java NumberGenerator 3000 200 > test7.txt
./ds 1000 test7.txt

echo
echo "test8";
java NumberGenerator 3000 400 > test8.txt
./ds 1000 test8.txt

echo
echo "test9";
java NumberGenerator 3000 600 > test9.txt
./ds 1000 test9.txt
echo

rm test*.txt;
rm NumberGenerator.class
