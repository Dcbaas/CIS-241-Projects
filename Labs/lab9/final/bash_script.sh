#/usr/bin/bash

sort -t, -k2 lab9.dat >lab9a.dat
gawk -F, '{printf "%s\t%s\t%s\n", $3, $2, $1}' lab9a.dat >lab9b.dat
sed -n -e 's/Fall /F/p' -e 's/Winter /W/p' lab9b.dat >lab9c.dat

test_path=course/cis241/example/blah/foo/demo.c
echo $test_path | gawk -F/ '{print $NF}' >output.txt
