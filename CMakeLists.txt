cmake_minimum_required(VERSION 3.12)
project(AP1)

set(CMAKE_CXX_STANDARD 14)

set(MAIN main.cpp)

set(AIRPLANE_MANAGEMENT
        # MyImplementation
        Airplane_Company_Management/MyImplementation.cpp Airplane_Company_Management/MyImplementation.h
        # File Parsing
        Airplane_Company_Management/File_Parsing/ParseHandling.cpp Airplane_Company_Management/File_Parsing/ParseHandling.h
        # File Parsing Util
        Airplane_Company_Management/File_Parsing/File_Parsing_Utility/Line.h
        # Interface
        Airplane_Company_Management/interface.h
        # ID
        # Employee
        Airplane_Company_Management/MyEmployee.cpp Airplane_Company_Management/MyEmployee.h
        # Plane
        Airplane_Company_Management/MyPlane.cpp Airplane_Company_Management/MyPlane.h
        #Flight
        Airplane_Company_Management/MyFlight.cpp Airplane_Company_Management/MyFlight.h
        # Date
        Airplane_Company_Management/Date.cpp
        # Reservation
        Airplane_Company_Management/MyReservation.cpp Airplane_Company_Management/MyReservation.h
        # Customer
        Airplane_Company_Management/MyCustomer.cpp Airplane_Company_Management/MyCustomer.h
        # DescriptorsFactory
        Airplane_Company_Management/Descriptors/DescriptorsFactory.cpp Airplane_Company_Management/Descriptors/DescriptorsFactory.h
        # Descriptor
        Airplane_Company_Management/Descriptors/Descriptor.cpp Airplane_Company_Management/Descriptors/Descriptor.h

        # ---- UTILITY ----
        # StringsUtility
        Airplane_Company_Management/Utility/StringsUtility.cpp
        # OperatorsHandling
        Airplane_Company_Management/Utility/OperatorsHandling.cpp Airplane_Company_Management/Utility/OperatorsHandling.h)

add_executable(ex2 ${AIRPLANE_MANAGEMENT} ${MAIN})