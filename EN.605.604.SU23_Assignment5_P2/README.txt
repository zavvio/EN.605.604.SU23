For assignment 5 program 2, we can summarize the problem into two requirements.
1. Be compatible with any existing or future classes.
2. Be able to "write to a file" in different mode (text vs binary, or more).

To satisfy (1), we must utilize the template "pattern" which specify the interface (its capability) in "Serializable.h";
Here, no matter what the class (Song/Date/Movie) is, it must be capable of performing Read, Write and Display to a specific destination (file path);
With the template interface properly initialized, the compiler would automatically generate equivalent code for each specific class.

For (2), we want variations to HOW a specific action, such as Write, be performed.
To achieve that, we extends (inherit from Serializable.h) into customized concrete implementations (e.g. SerializableSong.h), known as Strategy.
Different modes of performing the same action can now be implemented by various version of strategies;
e.g. SerializableSongTextFile.h, SerializableSongBinaryFile.h, SerializableSongHttpSocket.h, SerializableSongSharedMemory.h
Since they all share the same parent "Serializable.h",
the user (main application main.c) can simply initialize an appropriate strategy base on application logic/policy;
and then pass it to a Serializable object pointer (variable "serializer");
a call to serializer->write() may now perform completely different things depending on which strategy was provided to it.

Another benefit to this Template + Strategy Pattern approach is that future class can also utilize such "Serializable.h" interface without modifying this interface's source code;
instead, we may create a new strategy for each new class by inheriting and implementing from the parent "Serializable.h".
As such, we aligned to the Closed-Open principle, "Serializable.h" is closed from modification but open to extension (and specialization);
and the same API to read/write/display may be reused across different classes and modes.

Steps to support new class:
Given a new class "Person";
Create a new concreate implementation "Serializable*.h" which inherit "Serializable.h";
In this new derived template, provide specialization to the Person class;
In the application, pass an instance of this new strategy to the Serializable type pointer;
Trigger the virtual functions.