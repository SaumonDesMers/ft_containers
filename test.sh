cpp_version="-std=c++98"
flags="-Wall -Werror -Wextra -g"
src="src/main.cpp src/test_vector.cpp src/test_stack.cpp src/test_map.cpp"
valgrind="valgrind --tool=memcheck --leak-check=full --leak-resolution=high --track-origins=yes --show-reachable=yes --log-file=valgrind.log"

if [ "$1" = "ft" ]
then
	c++ $flags $cpp_version -I include $src -o ft_containers
elif [ "$1" = "std" ]
then
	c++ $flags $cpp_version -I include -D STD $src -o std_containers
elif [ "$1" = "rm" ]
then
	rm ft_containers std_containers ft_output std_output valgrind.log
elif [ "$1" = "diff" ]
then
	$valgrind ./std_containers > std_output
	$valgrind ./ft_containers > ft_output
	diff ft_output std_output
else
	$0 ft
	$0 std

	$0 diff
fi
