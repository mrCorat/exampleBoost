#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <iostream>
#include <string>

// Используем встроенный тег vertex_name_t из Boost
typedef boost::adjacency_list<
    boost::vecS, 
    boost::vecS, 
    boost::directedS,
    boost::property<boost::vertex_name_t, std::string>  // Используем стандартный тег
> Graph;

// Visitor с использованием стандартного тега
struct route_printer_visitor : public boost::default_dfs_visitor {
    boost::property_map<Graph, boost::vertex_name_t>::type name_map;

    route_printer_visitor(Graph& g) : name_map(boost::get(boost::vertex_name, g)) {}

    void discover_vertex(Graph::vertex_descriptor v, const Graph& g) const {
        std::cout << "Посещаем город: " << name_map[v] << "\n";
    }
};

int main() {
    Graph g;

    // Добавляем вершины с именами
    auto v0 = boost::add_vertex(g); boost::get(boost::vertex_name, g)[v0] = "Москва";
    auto v1 = boost::add_vertex(g); boost::get(boost::vertex_name, g)[v1] = "Санкт-Петербург";
    auto v2 = boost::add_vertex(g); boost::get(boost::vertex_name, g)[v2] = "Казань";

    // Добавляем ребра
    boost::add_edge(v0, v1, g);
    boost::add_edge(v0, v2, g);
    boost::add_edge(v2, v1, g);

    // Запускаем DFS
    std::cout << "--- Начало обхода в глубину (DFS) ---\n";
    route_printer_visitor vis(g);
    boost::depth_first_search(g, boost::visitor(vis).root_vertex(v0));

    return 0;
}
