#pragma once

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cstdint>
#include <type_traits>

namespace details {

    template <typename T>
    struct is_container: std::false_type {};

    // partial specializations for vector
    template <typename T, typename Alloc>
    struct is_container<std::vector<T, Alloc>>: std::true_type {};

    // partial specializations for list
    template <typename T, typename Alloc>
    struct is_container<std::list<T, Alloc>>: std::true_type {};
}

template<typename T, typename = typename
    std::enable_if_t<
        std::is_integral<T>::value,
        void
    >
>
void printIp(T ip)
{
    uint8_t  octets[sizeof(T)];
    *(T*)octets = ip; 
    for (int i = sizeof(octets) - 1; i != 0; i--)
    {
        std::cout << +octets[i] << ".";
    }
    std::cout << +octets[0] << std::endl;  
}

void printIp(const std::string &ip) 
{
    std::cout << ip << std::endl;
}


template<typename T, typename = typename 
    std::enable_if_t<
        details::is_container<T>::value,
        void
    >
>
void printIp(const T & ip) {
    for (auto ipIt = ip.cbegin(); ipIt != ip.cend();  ) {
        std::cout << *ipIt;
        if (++ipIt != ip.cend()) {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}
