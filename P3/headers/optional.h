//
// Created by Rafael Bardisa Rodes on 14/2/23.
//
#ifndef COMPILERS_PROJECT_GB_OPTIONAL_H
#define COMPILERS_PROJECT_GB_OPTIONAL_H

/**
 * factory of optional types. Optional.ok signifies whether the value should be treated as valid or not<br>
 * usage:
 * @code typedef optional(char) Option_char; //define an optional<char> type
 * @endcode
 * then you can declare functions as:
 * @code
 * Option_char foo(int bar){
 *
 *     //null option type signals error/unexpected value inside function
 *     if (!bar) return (Option_char){0};
 *
 *     //normal execution returns a valid option
 *     Option_char res = {
 *         .ok = TRUE,
 *         .value = 'z',
 *     };
 *     return res;
 * @endcode
 * Optional types are not needed in c. However, they explicitly signal that a function may return an invalid value or run into a problem:
 * @code
 * int main(){
 *     // function could return an invalid value
 *     Option_char baz = foo(2);
 *
 *     // handle error as fit
 *     if(!baz.ok) return -1;
 *
 *     //else continue with program execution ensuring a valid value
 *     char baz_val = baz.value;
 *     ...
 * }
 * @endcode
 * In the long run, they can be used to keep track of the growing number of functions of the project.<br>
 * It is best practice to use mostly for return types, not parameters (I think)
 */
#define optional(type) struct Option_##type{char ok; type value;}
//same but also works with references
#define optional_ref(type) struct Option_##type{char ok; type* value;}

#endif //COMPILERS_PROJECT_GB_OPTIONAL_H
