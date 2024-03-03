#pragma once

#include <vector>
#include <list>
#include <string>
#include <iostream>
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

void printIp(int8_t ip)
{
    std::cout << +static_cast<uint8_t>(ip) << std::endl;
}

void printIp(int16_t ip)
{
    union uIp {
        uint16_t ip;
        uint8_t  octets[2];
    } innerIp;
    innerIp.ip = ip;
    std::cout << +innerIp.octets[1] << "."
              << +innerIp.octets[0] << std::endl; 
}

void printIp(int32_t ip)
{
    union uIp {
        uint32_t ip;
        uint8_t  octets[4];
    } innerIp;
    innerIp.ip = ip;
    std::cout << +innerIp.octets[3] << "." 
              << +innerIp.octets[2] << "."
              << +innerIp.octets[1] << "."
              << +innerIp.octets[0] << std::endl; 
}

void printIp(int64_t ip)
{
    union uIp {
        uint64_t ip;
        uint8_t  octets[8];
    } innerIp;
    innerIp.ip = ip;
    std::cout << +innerIp.octets[7] << "." 
              << +innerIp.octets[6] << "."
              << +innerIp.octets[5] << "."
              << +innerIp.octets[4] << "."
              << +innerIp.octets[3] << "."
              << +innerIp.octets[2] << "."
              << +innerIp.octets[1] << "."
              << +innerIp.octets[0] << std::endl; 
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
