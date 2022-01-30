#include <iostream>

template<typename K>
class A
{
private:
	K _k;
public:
	A(K const& k) : _k(k) {}
	K get() const { return _k; }

	friend bool operator==(A const& lhs, A const& rhs)
	{
		return lhs.get() == rhs.get();
	}

	friend bool operator!=(A const& lhs, A const& rhs)
	{
		return !(lhs == rhs);
	}
};

template<typename K>
class B
{
	K _v;
public:
	B(K const& v) : _v(v) {}
	B(A<K> a) : _v(a.get()) {}
	K get() const { return _v; }

	friend bool operator==(B const& lhs, B const& rhs)
	{
		return lhs.get() == rhs.get();
	}

	friend bool operator!=(B const& lhs, B const& rhs)
	{
		return !(lhs == rhs);
	}
};

/*template<typename K>
bool operator==(A<K> const& lhs, A<K> const& rhs)
{
	return lhs.get() == rhs.get();
}

template<typename K>
bool operator!=(A<K> const& lhs, A<K> const& rhs)
{
	return !(lhs == rhs);
}

template<typename K>
bool operator==(B<K> const& lhs, B<K> const& rhs)
{
	return lhs.get() == rhs.get();
}

template<typename K>
bool operator!=(B<K> const& lhs, B<K> const& rhs)
{
	return !(lhs == rhs);
}*/

int main(void)
{
	A<std::string> a("Hello");
	B<std::string> b("Hello");
	bool v = a == b;
	if (v)
		std::cout << "Matched!" << std::endl;
	else
		std::cout << "Not matched!" << std::endl;
	return 0;
}
