//
// Created by Tamás Horváth on 7/5/22.
//

#include "unique_ptr.h"

namespace mstl {

    template<class T, class Deleter>
    constexpr
    unique_ptr<T, Deleter>::unique_ptr() noexcept
    requires
        std::is_nothrow_default_constructible_v<Deleter> &&
        (!std::is_pointer_v<Deleter>)
        : m_data{{}}, m_deleter{{}} {}

    template<class T, class Deleter>
    constexpr
    unique_ptr<T, Deleter>::unique_ptr( std::nullptr_t ) noexcept
    requires
        std::is_nothrow_default_constructible_v<Deleter> &&
        (!std::is_pointer_v<Deleter>)
        : m_data{{}}, m_deleter{{}} {}

    template<class T, class Deleter>
    constexpr
    unique_ptr<T, Deleter>::unique_ptr( pointer p ) noexcept
    requires
        std::is_nothrow_default_constructible_v<Deleter> &&
        (!std::is_pointer_v<Deleter>)
        : m_data{ p }, m_deleter{{}} {}

    template<class T, class Deleter>
    constexpr
    unique_ptr<T, Deleter>::unique_ptr( pointer p, const deleter_type& d ) noexcept
    requires
        std::is_nothrow_copy_constructible_v<Deleter> &&
        (!std::is_reference_v<Deleter>) &&
        std::is_constructible_v<Deleter, decltype(d)>
        : m_data{ p }, m_deleter{ d } {}

    template<class T, class Deleter>
    constexpr
    unique_ptr<T, Deleter>::unique_ptr( pointer p, deleter_type& d ) noexcept
    requires
        std::is_nothrow_copy_constructible_v<Deleter> &&
        std::is_lvalue_reference_v<Deleter> &&
        std::is_constructible_v<Deleter, decltype(d)>
        : m_data{ p }, m_deleter{ d } {}

    template<class T, class Deleter>
    constexpr
    unique_ptr<T, Deleter>::unique_ptr( pointer p, const deleter_type& d ) noexcept
    requires
        std::is_nothrow_copy_constructible_v<Deleter> &&
        std::is_lvalue_reference_v<Deleter> &&
        std::is_constructible_v<Deleter, decltype(d)>
        : m_data{ p }, m_deleter{ d } {}


    template<class T, class Deleter>
    constexpr
    unique_ptr<T, Deleter>::unique_ptr( pointer p, const deleter_type&& d ) noexcept
    requires
        std::is_nothrow_move_constructible_v<Deleter> &&
        (!std::is_reference_v<Deleter>) &&
        std::is_constructible_v<Deleter, decltype(d)>
        : m_data{ p }, m_deleter{ d } {}

    template<class T, class Deleter>
    constexpr unique_ptr<T, Deleter>::unique_ptr( unique_ptr&& other ) noexcept requires
        std::is_move_constructible_v<Deleter> &&
        (!std::is_reference_v<Deleter>) {
        m_data = std::move( other.m_data );
        m_deleter = std::move( other.m_deleter );
        other.m_data = nullptr;
    }

    template<class T, class Deleter>
    constexpr unique_ptr<T, Deleter>::unique_ptr( unique_ptr&& other ) noexcept requires
        std::is_move_constructible_v<Deleter> &&
        std::is_reference_v<Deleter>
        : m_deleter { other.m_deleter } {
        m_data = std::move( other.m_data );
        other.m_data = nullptr;
    }
}