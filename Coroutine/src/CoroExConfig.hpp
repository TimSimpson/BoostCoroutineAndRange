#ifndef FILE_GUARD_COROEX_CONFIG_HPP
#define FILE_GUARD_COROEX_CONFIG_HPP

#include <boost/config.hpp>

#if defined(BOOST_ALL_DYN_LINK) || defined(COROEX_DYN_LINK)
    #if defined(COROEX_BUILD)
        #define COROEX BOOST_SYMBOL_EXPORT
    #else
        #define COROEX BOOST_SYMBOL_IMPORT
    #endif
#else
    #define COROEX
#endif

#endif
