cpp_version="-std=c++98"
flags="-Wall -Werror -Wextra -g"
src="src/main.cpp"

if [ "$1" = "ft" ]
then
	c++ $flags $cpp_version -I include $src -o ft_containers
elif [ "$1" = "std" ]
then
	c++ $flags $cpp_version -I include -D STD $src -o std_containers
elif [ "$1" = "rm" ]
then
	rm ft_containers std_containers ft_output std_output
elif [ "$1" = "diff" ]
then
	./ft_containers > ft_output
	./std_containers > std_output
	diff -y ft_output std_output
else
	$0 ft
	$0 std

	$0 diff
fi
