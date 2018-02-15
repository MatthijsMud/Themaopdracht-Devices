//! @file
#ifndef NON_COPYABLE_HPP
#define NON_COPYABLE_HPP

//! @brief Utility class for making object non-copyable.
//! 
//! Classes that should not be copied (either by assigment or construction),
//! can extend from this class. This avoids the need to manually delete the copy
//! assignment operator and constructor. Make sure the inheritence is public.
class NonCopyable
{
protected:
	// The class "NonCopyable" is not intended to be used as references/pointers.
	// Instances of derived classes should be explicitly deleted; enforce that by
	// marking this destructor protected. 
	~NonCopyable();
private:
	NonCopyable(const NonCopyable &) = delete;
	NonCopyable & operator=(const NonCopyable &) = delete;
};

#endif // NON_COPYABLE_HPP
