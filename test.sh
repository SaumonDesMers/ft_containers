cpp_version="-std=c++98"
flags="-Wall -Werror -Wextra"

if [ "$1" = "ft" ]
then
	c++ $flags $cpp_version -I include src/main.cpp -o ft_containers
elif [ "$1" = "std" ]
then
	c++ $flags $cpp_version -I include -D STD src/main.cpp -o std_containers
elif [ "$1" = "rm" ]
then
	rm ft_containers std_containers ft_output std_output
else
	c++ $flags $cpp_version -I include src/main.cpp -o ft_containers
	c++ $flags $cpp_version -I include -D STD src/main.cpp -o std_containers

	./ft_containers > ft_output
	./std_containers > std_output

	diff ft_output std_output
fi
