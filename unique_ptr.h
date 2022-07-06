//
// Created by Tamás Horváth on 6/21/22.
//

#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <memory>
#include <type_traits>

namespace mstl {

    template<class T,
             class Deleter = std::default_delete<T>>
    class unique_ptr {

    public:

        using pointer = T*;
        using element_type = T;
        using deleter_type = Deleter;

//constructors
        constexpr unique_ptr() noexcept
        requires
            std::is_nothrow_default_constructible_v<Deleter> &&
            (!std::is_pointer_v<Deleter>);

        constexpr unique_ptr( std::nullptr_t ) noexcept
        requires
            std::is_nothrow_default_constructible_v<Deleter> &&
            (!std::is_pointer_v<Deleter>);

        constexpr explicit unique_ptr( pointer ) noexcept
        requires
            std::is_nothrow_default_constructible_v<Deleter> &&
            (!std::is_pointer_v<Deleter>);

        constexpr unique_ptr( pointer, const deleter_type& d ) noexcept
        requires
            std::is_nothrow_copy_constructible_v<Deleter> &&
            (!std::is_reference_v<Deleter>) &&
            std::is_constructible_v<Deleter , decltype(d)>;

        constexpr unique_ptr( pointer p, deleter_type& d ) noexcept
        requires
            std::is_nothrow_copy_constructible_v<Deleter> &&
            std::is_lvalue_reference_v<Deleter> &&
            std::is_constructible_v<Deleter , decltype(d)>;

        constexpr unique_ptr( pointer p, const deleter_type& d ) noexcept
        requires
            std::is_nothrow_copy_constructible_v<Deleter> &&
            std::is_lvalue_reference_v<Deleter> &&
            std::is_constructible_v<Deleter , decltype(d)>;

        constexpr unique_ptr( pointer p, const deleter_type&& d ) noexcept
        requires
            std::is_nothrow_move_constructible_v<Deleter> &&
            (!std::is_reference_v<Deleter>) &&
            std::is_constructible_v<Deleter , decltype(d)>;

        constexpr unique_ptr( pointer p, deleter_type&& d ) noexcept
        requires
            std::is_lvalue_reference_v<Deleter> &&
            std::is_constructible_v<Deleter , decltype(d)>
            = delete;

        constexpr unique_ptr( pointer p, const deleter_type&& d ) noexcept
        requires
            std::is_lvalue_reference_v<Deleter> &&
            std::is_constructible_v<Deleter , decltype(d)>
            = delete;

        constexpr unique_ptr( unique_ptr&& ) noexcept
        requires
            std::is_move_constructible_v<Deleter> &&
            (!std::is_reference_v<Deleter>);

        constexpr unique_ptr( unique_ptr&& ) noexcept
        requires
            std::is_move_constructible_v<Deleter> &&
            std::is_reference_v<Deleter>;

    private:
        T* m_data;
        Deleter m_deleter;
    };
} // mstl

#endif //UNIQUE_PTR_H
