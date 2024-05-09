#ifndef LCH_BIMAP_H
#define LCH_BIMAP_H

/*****************************/
/* Class documentations      */
/*****************************/

/*!
   \class cmap::Bimap
   \brief Class use to provide bi-directional map support.

   \b std::map provide fast-lookup when search value by key (complexity: <b>O(log(n))</b>) but
   when searching by value is needed, complexity increase (<b>O(n)</b>), \c std::map is
   simply not designed for this purpose. \n
   This class allow to provide fast lookup when searching by keys (<b>O(log(n))</b>) or by
   values (<b>O(log(n))</b>).

   \note
   Note that to provide fast-lookup on both entities, memory usage is doubled, so use
   this class <b>only</b> when you really need it.

   \note
   If you have dependency to \b Boost library (https://www.boost.org/), use
   \c Boost.Bimap (https://www.boost.org/doc/libs/1_79_0/libs/bimap/doc/html/index.html)
   instead of this class.
*/

#include <map>

namespace cmap{

/* Functions definitions */
template<class TypeKey, class TypeValue>
class Bimap
{
private:
    using _ContainerKey = std::map<TypeKey, TypeValue>;
    using _ContainerValue = std::map<TypeValue, TypeKey>;

    using _TypeNode = std::pair<TypeKey, TypeValue>; // Used to implement std::initializer_list<T> support

public:
    using iterator = typename _ContainerKey::iterator;
    using const_iterator = typename _ContainerKey::const_iterator;
    using reverse_iterator = typename _ContainerKey::reverse_iterator;
    using const_reverse_iterator = typename _ContainerKey::const_reverse_iterator;

public:
    Bimap();
    Bimap(const std::initializer_list<_TypeNode> &args);

public:
    bool empty() const;
    std::size_t size() const;
    std::size_t maxSize() const;

    void clear();
    void insert(const TypeKey &key, const TypeValue &value);
    void erase(const TypeKey &key);

    const TypeValue& getValue(const TypeKey &key) const;
    const TypeKey& getKey(const TypeValue &value) const;

private:
    void insert(_TypeNode &&node);
    void insert(const _TypeNode &node);

public:
    iterator begin();
    const_iterator cbegin() const;
    reverse_iterator rbegin();
    const_reverse_iterator crbegin() const;
    iterator end();
    const_iterator cend() const;
    reverse_iterator rend();
    const_reverse_iterator crend() const;

private:
    _ContainerKey m_map;
    _ContainerValue m_mapInversed;
};

/*
 * Functions implementations
 * Class use template and methods cannot be defined in .cpp file.
 * See https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl
 */

/*!
 * \brief Construct empty bimap
 */
template<class TypeKey, class TypeValue>
Bimap<TypeKey, TypeValue>::Bimap()
{
    clear();
}

/*!
 * \brief Construct bimap with \c std::initializer_list
 * \param args
 * List to use to construct bimap.
 *
 * <b>Example: </b>
 * \code{.c}
    const cmap::Bimap<int, std::string> m_mapNumberToString =
    {
        {1, "ONE"},
        {2, "TWO"},
        {3, "THREE"}
    };
 * \endcode
 */
template<class TypeKey, class TypeValue>
Bimap<TypeKey, TypeValue>::Bimap(const std::initializer_list<_TypeNode> &args)
{
    for(auto it=args.begin(); it != args.end(); ++it){
        insert(*it);
    }
}

/*!
 * \brief Checks whether the container is empty
 *
 * \return
 * Returns \c true if the container is empty, \c false otherwise
 */
template<class TypeKey, class TypeValue>
bool Bimap<TypeKey, TypeValue>::empty() const
{
    return m_map.empty();
}

/*!
 * \brief Returns the number of elements
 *
 * \return
 * The number of elements in the container
 */
template<class TypeKey, class TypeValue>
std::size_t Bimap<TypeKey, TypeValue>::size() const
{
    return m_map.size();
}

/*!
 * \brief Returns the maximum possible number of elements
 *
 * \return
 * Maximum number of elements
 */
template<class TypeKey, class TypeValue>
std::size_t Bimap<TypeKey, TypeValue>::maxSize() const
{
    return m_map.max_size();
}

/*!
 * \brief Clears the contents
 * \details
 * Erases all elements from the container. After this call, size() returns zero. \n
 * Invalidates any references, pointers, or iterators referring to contained elements. Any past-the-end iterator remains valid.
 */
template<class TypeKey, class TypeValue>
void Bimap<TypeKey, TypeValue>::clear()
{
    m_map.clear();
    m_mapInversed.clear();
}

/*!
 * \brief Insert item to bimap
 *
 * \param key
 * Key of element, if key already exist, it will be replaced.
 * \param value
 * Value associated to the key
 */
template<class TypeKey, class TypeValue>
void Bimap<TypeKey, TypeValue>::insert(const TypeKey &key, const TypeValue &value)
{
    m_map[key] = value;
    m_mapInversed[value] = key;
}

/*!
 * \overload
 */
template<class TypeKey, class TypeValue>
void Bimap<TypeKey, TypeValue>::insert(_TypeNode &&node)
{
    insert(node.first, node.second);
}

/*!
 * \overload
 */
template<class TypeKey, class TypeValue>
void Bimap<TypeKey, TypeValue>::insert(const _TypeNode &node)
{
    insert(node.first, node.second);
}

/*!
 * \brief Use to erase an element
 *
 * \param key
 * Key of element to erase, if key doesn't exist, this
 * method do nothing.
 */
template<class TypeKey, class TypeValue>
void Bimap<TypeKey, TypeValue>::erase(const TypeKey &key)
{
    /* Verify that key exists */
    auto it = m_map.find(key);
    if(it == m_map.cend()){
        return;
    }

    /* Remove item from both maps */
    m_mapInversed.erase(it->second);
    m_map.erase(it);
}

/*!
 * \brief Use to retrieve value by key
 *
 * \param key
 * Key of element to get.
 * \return
 * Return value associated to key.
 *
 * \throw std::out_of_range
 * Throw if key cannot be found
 */
template<class TypeKey, class TypeValue>
const TypeValue &Bimap<TypeKey, TypeValue>::getValue(const TypeKey &key) const
{
    return m_map.at(key);
}

/*!
 * \brief Use to retrieve key by value
 *
 * \param value
 * Value to use to retrieve key element.
 * \return
 * Return key associated to value.
 *
 * \throw std::out_of_range
 * Throw if value cannot be found
 */
template<class TypeKey, class TypeValue>
const TypeKey &Bimap<TypeKey, TypeValue>::getKey(const TypeValue &value) const
{
    return m_mapInversed.at(value);
}

/*!
 * \brief Returns an iterator to the beginning
 *
 * \return
 * Iterator to the first element. \n
 * If the map is empty, the returned iterator will be equal to \c end().
 */
template<class TypeKey, class TypeValue>
typename Bimap<TypeKey, TypeValue>::iterator Bimap<TypeKey, TypeValue>::begin()
{
    return m_map.begin();
}

/*!
 * \brief Returns a constant iterator to the beginning
 *
 * \return
 * Iterator to the first element. \n
 * If the map is empty, the returned iterator will be equal to \c cend().
 */
template<class TypeKey, class TypeValue>
typename Bimap<TypeKey, TypeValue>::const_iterator Bimap<TypeKey, TypeValue>::cbegin() const
{
    return m_map.cbegin();
}

/*!
 * \brief Returns a reverse iterator to the beginning
 * \details
 * Returns a reverse iterator to the first element of the reversed map.
 * It corresponds to the last element of the non-reversed map. \n
 *
 * \return
 * Reverse iterator to the first element. \n
 * If the map is empty, the returned iterator is equal to \c rend().
 */
template<class TypeKey, class TypeValue>
typename Bimap<TypeKey, TypeValue>::reverse_iterator Bimap<TypeKey, TypeValue>::rbegin()
{
    return m_map.rbegin();
}

/*!
 * \brief Returns a constant reverse iterator to the beginning
 * \details
 * Returns a reverse iterator to the first element of the reversed map.
 * It corresponds to the last element of the non-reversed map. \n
 *
 * \return
 * Reverse iterator to the first element. \n
 * If the map is empty, the returned iterator is equal to \c crend().
 */
template<class TypeKey, class TypeValue>
typename Bimap<TypeKey, TypeValue>::const_reverse_iterator Bimap<TypeKey, TypeValue>::crbegin() const
{
    return m_map.crbegin();
}

/*!
 * \brief Returns an iterator to the end
 *
 * \return
 * Iterator to the element following the last element.
 */
template<class TypeKey, class TypeValue>
typename Bimap<TypeKey, TypeValue>::iterator Bimap<TypeKey, TypeValue>::end()
{
    return m_map.end();
}

/*!
 * \brief Returns a constant iterator to the end
 *
 * \return
 * Iterator to the element following the last element.
 */
template<class TypeKey, class TypeValue>
typename Bimap<TypeKey, TypeValue>::const_iterator Bimap<TypeKey, TypeValue>::cend() const
{
    return m_map.cend();
}

/*!
 * \brief Returns a reverse iterator to the end
 * \details
 * Returns a reverse iterator to the element following the last element of the reversed map.
 * It corresponds to the element preceding the first element of the non-reversed map.
 *
 * \return
 * Reverse iterator to the element following the last element.
 */
template<class TypeKey, class TypeValue>
typename Bimap<TypeKey, TypeValue>::reverse_iterator Bimap<TypeKey, TypeValue>::rend()
{
    return m_map.rend();
}

/*!
 * \brief Returns a constant reverse iterator to the end
 * \details
 * Returns a reverse iterator to the element following the last element of the reversed map.
 * It corresponds to the element preceding the first element of the non-reversed map.
 *
 * \return
 * Reverse iterator to the element following the last element.
 */
template<class TypeKey, class TypeValue>
typename Bimap<TypeKey, TypeValue>::const_reverse_iterator Bimap<TypeKey, TypeValue>::crend() const
{
    return m_map.crend();
}

} // Namespace cmap

#endif // LCH_BIMAP_H
