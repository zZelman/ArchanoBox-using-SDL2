#pragma once

// This interface takes control of when objects' functionality get to start or stop.
//		This is different than a constructor because a constructor just initializes data fields,
//		the methods below are for functionality ie: start reading into a buffer
// All methods return a boolean to check for success
class IControlledStartStop
{
public:
	// Starting functionality
	virtual bool startFunctionality() = 0;

	// Stopping functionality
	virtual bool stopFunctionality() = 0;
};