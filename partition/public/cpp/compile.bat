@echo off

set problem=partition
set grader_name=stub

g++ -std=gnu++17 -O2 -pipe -o "%problem%" "%grader_name%.cpp" "%problem%.cpp"
