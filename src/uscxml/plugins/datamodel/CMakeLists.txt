if (BUILD_DM_ECMA)
	if (JSC_FOUND)
		set(USCXML_DATAMODELS "ecmascript(JSC) ${USCXML_DATAMODELS}")
		# JavaScriptCore ecmascript datamodel
		file(GLOB JSC_DATAMODEL
			ecmascript/JavaScriptCore/*.cpp
			ecmascript/JavaScriptCore/*.h
			ecmascript/*.cpp
			ecmascript/*.h
		)
		file(GLOB_RECURSE JSC_DOM
			ecmascript/JavaScriptCore/dom/*.cpp
			ecmascript/JavaScriptCore/dom/*.h
		)
		if (BUILD_AS_PLUGINS)
			source_group("JavaScriptCore" FILES ${JSC_DATAMODEL})
			source_group("dom" FILES ${JSC_DOM})
		
			add_library(
				datamodel_jsc SHARED 
				${JSC_DATAMODEL}
				${JSC_DOM}
				"../Plugins.cpp")
			target_link_libraries(datamodel_jsc  uscxml ${JSC_LIBRARY})
			set_target_properties(datamodel_jsc PROPERTIES FOLDER "Plugin DataModel")
			set_target_properties(datamodel_jsc PROPERTIES COMPILE_FLAGS "-DPLUMA_EXPORTS")
			set_target_properties(datamodel_jsc PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")
		else()		
			list (APPEND USCXML_FILES ${JSC_DATAMODEL})
			list (APPEND USCXML_FILES ${JSC_DOM})
			list (APPEND USCXML_OPT_LIBS ${JSC_LIBRARY})
		endif()
		
	elseif(V8_FOUND)

	# GOOGLE V8 ecmascript datamodel
		set(USCXML_DATAMODELS "ecmascript(V8) ${USCXML_DATAMODELS}")
		# set(ENV{V8_SRC} ${CMAKE_SOURCE_DIR}/../v8)
		if (V8_FOUND AND BUILD_DM_ECMA)
			file(GLOB V8_DATAMODEL
				ecmascript/v8/*.cpp
				ecmascript/v8/*.h
				ecmascript/*.cpp
				ecmascript/*.h
			)
			file(GLOB_RECURSE V8_DOM
				ecmascript/v8/dom/*.cpp
				ecmascript/v8/dom/*.h
			)

			if (BUILD_AS_PLUGINS)
				source_group("V8" FILES ${V8_DATAMODEL})
				source_group("dom" FILES ${V8_DOM})

				add_library(
					datamodel_v8 SHARED 
					${V8_DATAMODEL}
					${V8_DOM}
					"../Plugins.cpp")
				target_link_libraries(datamodel_v8 uscxml ${V8_LIBRARY})
				set_target_properties(datamodel_v8 PROPERTIES FOLDER "Plugin DataModel")
				set_target_properties(datamodel_v8 PROPERTIES COMPILE_FLAGS "-DPLUMA_EXPORTS")
				set_target_properties(datamodel_v8 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")
			else()
				list (APPEND USCXML_FILES ${V8_DATAMODEL})
				list (APPEND USCXML_FILES ${V8_DOM})
			endif()
		endif()
	elseif(SPIDERMONKEY_FOUND)
		set(USCXML_DATAMODELS "ecmascript(SpiderMonkey) ${USCXML_DATAMODELS}")
		# set(ENV{V8_SRC} ${CMAKE_SOURCE_DIR}/../v8)
		file(GLOB SPIDERMONKEY_DATAMODEL
			ecmascript/SpiderMonkey/*.cpp
			ecmascript/SpiderMonkey/*.h
			ecmascript/*.cpp
			ecmascript/*.h
		)

		if (BUILD_AS_PLUGINS)
			source_group("SpiderMonkey" FILES ${SPIDERMONKEY_DATAMODEL})

			add_library(
				datamodel_spidermonkey SHARED 
				${SPIDERMONKEY_DATAMODEL}
			"../Plugins.cpp")
			target_link_libraries(datamodel_spidermonkey uscxml ${SPIDERMONKEY_LIBRARY})
			set_target_properties(datamodel_spidermonkey PROPERTIES FOLDER "Plugin DataModel")
			set_target_properties(datamodel_spidermonkey PROPERTIES COMPILE_FLAGS "-DPLUMA_EXPORTS")
			set_target_properties(datamodel_spidermonkey PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")
		else()
			list (APPEND USCXML_FILES ${SPIDERMONKEY_DATAMODEL})
		endif()
	endif()
endif()


# NULL datamodel (not useful as plugin)

set(USCXML_DATAMODELS "null ${USCXML_DATAMODELS}")
file(GLOB NULL_DATAMODEL
	null/*.cpp
	null/*.h
)
list (APPEND USCXML_FILES ${NULL_DATAMODEL})


# Lua datamodel

if (BUILD_DM_LUA AND LUA_FOUND AND NOT BUILD_MINIMAL)
	set(USCXML_DATAMODELS "lua ${USCXML_DATAMODELS}")
	file(GLOB LUA_DATAMODEL
		lua/*.cpp
		lua/*.h
	)
	if (BUILD_AS_PLUGINS)
		source_group("" FILES ${LUA_DATAMODEL})
		add_library(datamodel_lua SHARED ${LUA_DATAMODEL} "../Plugins.cpp")
		target_link_libraries(datamodel_lua 
			uscxml
			${LUA_LIBRARIES}
		)
		set_target_properties(datamodel_lua PROPERTIES FOLDER "Plugin DataModel")
		set_target_properties(datamodel_lua PROPERTIES COMPILE_FLAGS "-DPLUMA_EXPORTS")
		set_target_properties(datamodel_lua PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")
	else()
		list (APPEND USCXML_FILES ${LUA_DATAMODEL})
	endif()
endif()


# XPath datamodel

if (BUILD_DM_XPATH AND NOT BUILD_MINIMAL)
	set(USCXML_DATAMODELS "xpath ${USCXML_DATAMODELS}")
	file(GLOB XPATH_DATAMODEL
		xpath/*.cpp
		xpath/*.h
	)
	if (BUILD_AS_PLUGINS)
		source_group("" FILES ${XPATH_DATAMODEL})
		add_library(datamodel_xpath SHARED ${XPATH_DATAMODEL} "../Plugins.cpp")
		target_link_libraries(datamodel_xpath uscxml)
		set_target_properties(datamodel_xpath PROPERTIES FOLDER "Plugin DataModel")
		set_target_properties(datamodel_xpath PROPERTIES COMPILE_FLAGS "-DPLUMA_EXPORTS")
		set_target_properties(datamodel_xpath PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")
	else()
		list (APPEND USCXML_FILES ${XPATH_DATAMODEL})
	endif()
endif()

# SWI PROLOG datamodel

if (SWI_FOUND AND BUILD_DM_PROLOG AND NOT BUILD_MINIMAL)
	set(USCXML_DATAMODELS "prolog ${USCXML_DATAMODELS}")
	
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/prolog/swi/SWIConfig.h.in ${CMAKE_BINARY_DIR}/uscxml/SWIConfig.h)
	
#	message(FATAL_ERROR "SWI_INCLUDE_DIR: ${SWI_INCLUDE_DIR}")

	# if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	# 	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -read_only_relocs suppress")
	# 	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -read_only_relocs suppress")
	# 	set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -read_only_relocs suppress")
	# 	set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -read_only_relocs suppress")
	# endif()
	file(GLOB_RECURSE SWI_DATAMODEL
		prolog/swi/*.cpp
		prolog/swi/*.h
	)
	if (BUILD_AS_PLUGINS)
		source_group("" FILES ${SWI_DATAMODEL})
		add_library(
			datamodel_swi SHARED 
			${SWI_DATAMODEL}
			"../Plugins.cpp")
		target_link_libraries(datamodel_swi 
			uscxml
			${GMP_LIBRARY}
			${CURSES_LIBRARIES}
			${SWI_LIBRARY})
		set_target_properties(datamodel_swi PROPERTIES FOLDER "Plugin DataModel")
		set_target_properties(datamodel_swi PROPERTIES COMPILE_FLAGS "-DPLUMA_EXPORTS")
		set_target_properties(datamodel_swi PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")
	else()
		list (APPEND USCXML_FILES ${SWI_DATAMODEL})
	endif()
endif()


# Promela datamodel

if (BUILD_DM_PROMELA AND NOT BUILD_MINIMAL)
	set(USCXML_DATAMODELS "promela ${USCXML_DATAMODELS}")
	
	file(GLOB_RECURSE PROMELA_DATAMODEL
		promela/*.cpp
		promela/*.c
		promela/*.h
	)
	if (BUILD_AS_PLUGINS)
		source_group("" FILES PROMELA_DATAMODEL)
		add_library(
			datamodel_promela SHARED 
			${PROMELA_DATAMODEL}
			"../Plugins.cpp")
		target_link_libraries(datamodel_promela uscxml)
		set_target_properties(datamodel_promela PROPERTIES FOLDER "Plugin DataModel")
		set_target_properties(datamodel_promela PROPERTIES COMPILE_FLAGS "-DPLUMA_EXPORTS")
		set_target_properties(datamodel_promela PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")
	else()
		list (APPEND USCXML_FILES ${PROMELA_DATAMODEL})
	endif()
endif()


set(USCXML_INCLUDE_DIRS ${USCXML_INCLUDE_DIRS} PARENT_SCOPE)
set(USCXML_FILES ${USCXML_FILES} PARENT_SCOPE)
set(USCXML_DATAMODELS ${USCXML_DATAMODELS} PARENT_SCOPE)
