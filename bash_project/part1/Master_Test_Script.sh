#/usr/bin/bash

#This is a list of test that I run to verify that the program is working correctly

#remove everything from before

rm -rf ~/backup
rm output.txt

echo "Adding individual file" >>output.txt
./backup.sh file1 >>output.txt

echo >>output.txt
echo "Adding a list of files" >>output.txt
./backup.sh file2 file3 >>output.txt

echo >>output.txt
echo "Adding duplicate file" >>output.txt
./backup.sh file1 file2 >>output.txt

echo >>output.txt
echo "Adding a directory" >>output.txt
./backup.sh test_dir/ >>output.txt

echo >>output.txt
echo "Contents of backup" >>output.txt
ls  ~/backup >>output.txt

echo >>output.txt
echo "Clear contents for next section" >>output.txt
rm ~/backup/* >>output.txt

echo >>output.txt
echo "Add files with the -s option enabled" >>output.txt
./backup.sh file1 file2 -s >>output.txt

echo >>output.txt
echo "Add the directory with the -c option enabled" >>output.txt
./backup.sh -c test_dir/ >>output.txt

echo >>output.txt
echo "Test the help option" >>output.txt
./backup.sh --help >>output.txt

echo >>output.txt
echo "Clear contents again" >>output.txt
rm ~/backup/* >>output.txt

echo >>output.txt
echo "Test cmd with all three args" >>output.txt
./backup.sh -c -s --help test_dir/ >>output.txt

echo >>output.txt
echo "Clear contents again" >>output.txt
rm ~/backup/* >>output.txt

echo >>output.txt
echo "Attempt to add an invalid file" >>output.txt
./backup.sh disco_file.txt >>output.txt

echo >>output.txt
echo "Attempt to add an invalid file within a set of valid files" >>output.txt
echo "Expected to copy all of the other files while showing an error message for the garbage file" >>output.txt
./backup.sh file1 disco_file file2 >>output.txt

echo >>output.txt
echo "done" >>output.txt
