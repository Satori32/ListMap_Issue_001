#include <iostream>
#include <list>
#include <string>
#include <utility>

template<class key_type, class value_type, class Al> class ListMap;

template<class key_type, class value_type> using LM_Allocater =  std::allocator<std::pair<key_type,value_type>>;

template<class key_type, class value_type,class Al = LM_Allocater<key_type,value_type>>
class ListMap {
	using pair_type = std::pair<const key_type, value_type>;
	using list_type = std::list<pair_type, Al>;
	list_type lst;
public:
	value_type& operator[](const key_type& key) {
		for (auto& p : lst) {
			if (p.first == key) {
				return p.second;
			}
		}
		lst.emplace_back(key, value_type());
		return lst.back().second;
	}
	void erase(const key_type& key) {
		for (auto it = lst.begin(); it != lst.end(); ++it) {
			if (it->first == key) {
				lst.erase(it);
				return;
			}
		}
	}
	void print() const {
		for (const auto& p : lst) {
			std::cout << p.first << ": " << p.second << std::endl;
		}
	}
	size_t size() const {
		return lst.size();
	}
	bool empty() const {
		return lst.empty();
	}
	void clear() {
		lst.clear();
	}
	//list_type& get_list() {
	//	return lst;
	//}

	using iterator = typename list_type::iterator;
	iterator begin() {
		return lst.begin();
	}
	iterator end() {
		return lst.end();
	}
	using const_iterator = typename list_type::const_iterator;
	const_iterator begin() const {
		return lst.begin();
	}
	const_iterator end() const {
		return lst.end();
	}
	const_iterator cbegin() const {
		return lst.cbegin();
	}	
	const_iterator cend() const {
		return lst.cend();
	}
	using allocator_type = Al;
	allocator_type get_allocator() const {
		return lst.get_allocator();
	}
	ListMap(const allocator_type& al = allocator_type()) : lst(al) {}
	ListMap(const ListMap& other) : lst(other.lst) {}
	ListMap(ListMap&& other) noexcept : lst(std::move(other.lst)) {}
	ListMap& operator=(const ListMap& other) {
		if (this != &other) {
			lst = other.lst;
		}
		return *this;
	}
	ListMap& operator=(ListMap&& other) noexcept {
		if (this != &other) {
			lst = std::move(other.lst);
		}
		return *this;
	}
	~ListMap() = default;
};
int main() {
	//ListMap<std::string, int, std::allocator<std::pair<const std::string, int>>> lm;
	ListMap<std::string, int> lm;
	lm["apple"] = 1;
	lm["banana"] = 2;
	lm["orange"] = 3;
	lm.print();
	std::cout << "Size: " << lm.size() << std::endl;
	lm.erase("banana");
	lm.print();
	std::cout << "Size: " << lm.size() << std::endl;
	return 0;
}