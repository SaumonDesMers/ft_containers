c++ -Wall -Werror -Wextra -std=c++98 -I include src/main.cpp -o ft_containers
c++ -Wall -Werror -Wextra -std=c++98 -I include -D STD src/main.cpp -o std_containers

./ft_containers > ft_output
./std_containers > std_output

diff ft_output std_output

rm ft_containers std_containers ft_output std_output