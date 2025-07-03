#pragma once

#include "HashTable.h"

template<typename Key, typename T, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class Unordered_MultiMap
{
private:
	using Table = HashTable<Key, T, Hash, KeyEqual, true>;
	Table _table;

public:
	using key_type = Key;
	using mapped_type = T;
	using value_type = typename Table::value_type;
	using hasher = Hash;
	using key_equal = KeyEqual;
	using size_type = typename Table::size_type;

	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;

	using iterator = typename Table::iterator;
	using const_iterator = typename Table::const_iterator;


	Unordered_MultiMap();
	~Unordered_MultiMap();

	explicit Unordered_MultiMap(size_type bucket_count, const hasher& hash = hasher(), const key_equal& equal = key_equal());

	template<typename InputIt>
	Unordered_MultiMap(InputIt first, InputIt last,
		size_type bucket_count = 0, const hasher& hash = hasher(), const key_equal& equal = key_equal());

	Unordered_MultiMap(std::initializer_list<value_type> ilist, 
		size_type bucket_count = 0, const hasher& hash = hasher(), const key_equal& equal = key_equal());

	Unordered_MultiMap(const Unordered_MultiMap&);
	Unordered_MultiMap(Unordered_MultiMap&&) noexcept;

	Unordered_MultiMap& operator=(const Unordered_MultiMap&);
	Unordered_MultiMap& operator=(Unordered_MultiMap&&) noexcept;
	Unordered_MultiMap& operator=(std::initializer_list<value_type> ilist);

	iterator begin() noexcept;
	iterator end() noexcept;
	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;
	const_iterator cbegin() const noexcept;
	const_iterator cend() const noexcept;

	[[nodiscard]] bool empty() const noexcept;
	[[nodiscard]] size_type size() const noexcept;

	void clear() noexcept;

	iterator insert(const value_type& value);
	iterator insert(value_type&& value);

	template<typename InputIt>
	void insert(InputIt first, InputIt last);

	void insert(std::initializer_list<value_type> ilist);

	template<typename... Args>
	iterator emplace(Args&&... args);

	size_type erase(const key_type& key);

	void swap(Unordered_MultiMap& other) noexcept(noexcept(_table.swap(other._table)));

	size_type count(const key_type& key) const;

	std::pair<iterator, iterator> equal_range(const key_type& key);
	std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const;

	iterator find(const key_type& key);
	const_iterator find(const key_type& key) const;

	[[nodiscard]] size_type bucket_count() const noexcept;
	size_type bucket_size(size_type index) const;
	size_type bucket(const key_type& key) const;

	float load_factor() const noexcept;
	float max_load_factor() const noexcept;
	void max_load_factor(float ml);

	void rehash(size_type count);
	void reserve(size_type count);

	bool operator==(const Unordered_MultiMap& other) const;
	bool operator!=(const Unordered_MultiMap& other) const;
};

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline Unordered_MultiMap<Key, T, Hash, KeyEqual>::Unordered_MultiMap() = default;

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline Unordered_MultiMap<Key, T, Hash, KeyEqual>::~Unordered_MultiMap() = default;

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline Unordered_MultiMap<Key, T, Hash, KeyEqual>::Unordered_MultiMap(
		size_type bucket_count, const hasher& hash, const key_equal& equal)
	: _table(bucket_count, hash, equal)
{
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline Unordered_MultiMap<Key, T, Hash, KeyEqual>::Unordered_MultiMap(std::initializer_list<value_type> ilist, 
	size_type bucket_count, const hasher& hash, const key_equal& equal)
	: _table(bucket_count, hash, equal)
{
	insert(ilist.begin(), ilist.end());
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline Unordered_MultiMap<Key, T, Hash, KeyEqual>::Unordered_MultiMap(const Unordered_MultiMap&) = default;

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline Unordered_MultiMap<Key, T, Hash, KeyEqual>::Unordered_MultiMap(Unordered_MultiMap&&) noexcept = default;

template<typename Key, typename T, typename Hash, typename KeyEqual>
template<typename InputIt>
inline Unordered_MultiMap<Key, T, Hash, KeyEqual>::Unordered_MultiMap(InputIt first, InputIt last, 
	size_type bucket_count, const hasher& hash, const key_equal& equal)
	: _table(bucket_count, hash, equal)
{
	insert(first, last);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline Unordered_MultiMap<Key, T, Hash, KeyEqual>&
		Unordered_MultiMap<Key, T, Hash, KeyEqual>::operator=(const Unordered_MultiMap&) = default;

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline Unordered_MultiMap<Key, T, Hash, KeyEqual>& 
		Unordered_MultiMap<Key, T, Hash, KeyEqual>::operator=(Unordered_MultiMap&&) noexcept = default;

template<typename Key, typename T, typename Hash, typename KeyEqual>
Unordered_MultiMap<Key, T, Hash, KeyEqual>& 
		Unordered_MultiMap<Key, T, Hash, KeyEqual>::operator=(std::initializer_list<value_type> ilist)
{
	clear();
	insert(ilist.begin(), ilist.end());
	return *this;
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::iterator Unordered_MultiMap<Key, T, Hash, KeyEqual>::begin() noexcept
{
	return _table.begin();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::iterator Unordered_MultiMap<Key, T, Hash, KeyEqual>::end() noexcept
{
	return _table.end();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::const_iterator Unordered_MultiMap<Key, T, Hash, KeyEqual>::begin() const noexcept
{
	return _table.begin();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::const_iterator Unordered_MultiMap<Key, T, Hash, KeyEqual>::end() const noexcept
{
	return _table.end();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::const_iterator Unordered_MultiMap<Key, T, Hash, KeyEqual>::cbegin() const noexcept
{
	return _table.cbegin();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::const_iterator Unordered_MultiMap<Key, T, Hash, KeyEqual>::cend() const noexcept
{
	return _table.cend();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
[[nodiscard]] bool Unordered_MultiMap<Key, T, Hash, KeyEqual>::empty() const noexcept
{
	return _table.empty();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::size_type Unordered_MultiMap<Key, T, Hash, KeyEqual>::size() const noexcept
{
	return _table.size();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
void Unordered_MultiMap<Key, T, Hash, KeyEqual>::clear() noexcept
{
	_table.clear();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::iterator 
		Unordered_MultiMap<Key, T, Hash, KeyEqual>::insert(const value_type& value)
{
	return _table.insert(value).first;
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::iterator Unordered_MultiMap<Key, T, Hash, KeyEqual>::insert(value_type&& value)
{
	return _table.insert(std::move(value)).first;
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
template<typename InputIt>
inline void Unordered_MultiMap<Key, T, Hash, KeyEqual>::insert(InputIt first, InputIt last)
{
	for (; first != last; ++first)
		insert(*first);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
void Unordered_MultiMap<Key, T, Hash, KeyEqual>::insert(std::initializer_list<value_type> ilist)
{
	insert(ilist.begin(), ilist.end());
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
template<typename... Args>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::iterator Unordered_MultiMap<Key, T, Hash, KeyEqual>::emplace(Args&&... args)
{
	return _table.emplace(std::forward<Args>(args)...);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::size_type Unordered_MultiMap<Key, T, Hash, KeyEqual>::erase(const key_type& key)
{
	return _table.erase(key);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline void Unordered_MultiMap<Key, T, Hash, KeyEqual>::swap(Unordered_MultiMap& other) noexcept(noexcept(_table.swap(other._table)))
{
	_table.swap(other._table);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::size_type 
		Unordered_MultiMap<Key, T, Hash, KeyEqual>::count(const key_type& key) const
{
	return _table.count(key);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
std::pair<typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::iterator, 
		typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::iterator> 
		Unordered_MultiMap<Key, T, Hash, KeyEqual>::equal_range(const key_type& key)
{
	return _table.equal_range(key);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
std::pair<typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::const_iterator, 
		typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::const_iterator> 
		Unordered_MultiMap<Key, T, Hash, KeyEqual>::equal_range(const key_type& key) const
{
	return _table.equal_range(key);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::iterator Unordered_MultiMap<Key, T, Hash, KeyEqual>::find(const key_type& key)
{
	return _table.find(key);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::const_iterator 
		Unordered_MultiMap<Key, T, Hash, KeyEqual>::find(const key_type& key) const
{
	return _table.find(key);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::size_type Unordered_MultiMap<Key, T, Hash, KeyEqual>::bucket_count() const noexcept
{
	return _table.bucket_count();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::size_type 
		Unordered_MultiMap<Key, T, Hash, KeyEqual>::bucket_size(size_type index) const
{
	return _table.bucket_size(index);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
typename Unordered_MultiMap<Key, T, Hash, KeyEqual>::size_type 
		Unordered_MultiMap<Key, T, Hash, KeyEqual>::bucket(const key_type& key) const
{
	return _table.bucket(key);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
float Unordered_MultiMap<Key, T, Hash, KeyEqual>::load_factor() const noexcept
{
	return _table.load_factor();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
float Unordered_MultiMap<Key, T, Hash, KeyEqual>::max_load_factor() const noexcept
{
	return _table.max_load_factor();
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
void Unordered_MultiMap<Key, T, Hash, KeyEqual>::max_load_factor(float ml)
{
	_table.max_load_factor(ml);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
void Unordered_MultiMap<Key, T, Hash, KeyEqual>::rehash(size_type count)
{
	_table.rehash(count);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
void Unordered_MultiMap<Key, T, Hash, KeyEqual>::reserve(size_type count)
{
	_table.reserve(count);
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline bool Unordered_MultiMap<Key, T, Hash, KeyEqual>::operator==(const Unordered_MultiMap& other) const
{
	return _table == other._table;
}

template<typename Key, typename T, typename Hash, typename KeyEqual>
inline bool Unordered_MultiMap<Key, T, Hash, KeyEqual>::operator!=(const Unordered_MultiMap& other) const
{
	return !(*this == other);
}
