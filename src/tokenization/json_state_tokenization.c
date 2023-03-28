// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include "json_token.h"

// // also checks json syntax

// json_token *json_state_tokenization(char *input)
// {

//     token_state token_current_state = TOKEN_STATE_START;

//     int curr_pos = 0, curr_array_pos = 0, counter;
//     char *buffer;

//     json_token *json_token_arr = (json_token *)malloc(sizeof(json_token) * strlen(input));

//     while (input[curr_pos] != '\0')
//     {
//         // printf("%d \n", curr_pos);
//         switch (token_current_state)
//         {

//         case TOKEN_STATE_START:

//             switch (input[curr_pos])
//             {
//             case '{':
//                 token_current_state = TOKEN_STATE_OBJECT_START;
//                 json_token_arr[curr_array_pos].type = TOKEN_TYPE_OBJECT_BEGIN;
//                 curr_array_pos++;
//                 break;

//             case '[':
//                 token_current_state = TOKEN_STATE_ARRAY_START;
//                 json_token_arr[curr_array_pos].type = TOKEN_TYPE_ARRAY_START;
//                 curr_array_pos++;
//                 break;

//             case ' ':
//                 break;

//             default:
//                 // raise error
//                 return NULL;
//             }

//             break;

//         case TOKEN_STATE_OBJECT_START:
//             switch (input[curr_pos])
//             {
//             case '"':
//                 token_current_state = TOKEN_STATE_KEY;
//                 json_token_arr[curr_array_pos].type = TOKEN_TYPE_STRING;

//                 for (int i = curr_pos+1; input[i] != '"'; i++)
//                 {
//                     if (input[i] == '\n')
//                     {
//                         // raise error, as it should be in single line. will check and decide what to do later.
//                         return NULL;
//                     }
//                     counter++;
//                 }

//                 buffer = (char *)malloc(sizeof(char) * (counter + 1)); // +1 for '\0'

//                 strncpy(buffer, input + curr_pos + 1, counter);
//                 buffer[counter] = '\0';

//                 json_token_arr[curr_array_pos].value = buffer;

//                 // free(buffer);
//                 curr_array_pos++;
//                 curr_pos += counter;
//                 counter = 0;
//                 break;

//             case ' ':
//                 break;

//             default:
//                 break;
//             }

//         case TOKEN_STATE_KEY:
//             switch (input[curr_pos])
//             {
//             case ':':
//                 token_current_state = TOKEN_STATE_COLON;
//                 json_token_arr[curr_array_pos].type = TOKEN_TYPE_COLON;
//                 curr_array_pos++;
//                 break;

//             case ' ':
//                 break;

//             default:
//                 break;
//             }
//             break;

//         case TOKEN_STATE_COLON:
//             switch (input[curr_pos])
//             {
//             case '"':
//                 token_current_state = TOKEN_STATE_VALUE;
//                 json_token_arr[curr_array_pos].type = TOKEN_TYPE_STRING;

//                 for (int i = curr_pos+1; input[i] != '"'; i++)
//                 {
//                     if (input[i] == '\n')
//                     {
//                         // raise error, as it should be in single line. will check and decide what to do later.
//                         return NULL;
//                     }
//                     counter++;
//                 }

//                 buffer = (char *)malloc(sizeof(char) * (counter + 1)); // +1 for '\0'

//                 strncpy(buffer, input + curr_pos + 1, counter);
//                 buffer[counter] = '\0';

//                 json_token_arr[curr_array_pos].value = buffer;

//                 // free(buffer);
//                 curr_array_pos++;
//                 curr_pos += counter;
//                 counter = 0;
//                 break;

//             case '[':
//                 break;

//             case '{':
//                 break;

//             case '0':
//             case '1':
//             case '2':
//             case '3':
//             case '4':
//             case '5':
//             case '6':
//             case '7':
//             case '8':
//             case '9':
//             case '-':
//                 token_current_state = TOKEN_STATE_VALUE;
//                 json_token_arr[curr_array_pos].type = TOKEN_TYPE_NUMBER;

//                 for (int i = curr_pos; isdigit(input[i]) || input[i] == '-'; i++)
//                 {
//                     counter++;
//                 }

//                 buffer = (char *)malloc(sizeof(char) * counter + 1);
//                 strncpy(buffer, input + curr_pos, counter);
//                 buffer[counter] = '\0';
//                 json_token_arr[curr_array_pos].value = buffer;

//                 // free(buffer);
//                 curr_pos += counter - 1; // subtracting `-1` bcz curr_pos is at pointer of first digit, so we don't need to add it again.
//                 curr_array_pos++;
//                 counter = 0;
//                 break;

//             case ' ':
//                 break;

//             default:
//                 break;
//             }

//         case TOKEN_STATE_VALUE:
//             switch (input[curr_pos])
//             {
//             case ',':
//                 token_current_state = TOKEN_STATE_COMMA;
//                 json_token_arr[curr_array_pos].type = TOKEN_TYPE_COMMA;
//                 curr_array_pos++;
//                 break;

//             case ' ':
//                 break;
            
//             default:
//                 break;
//             }

//         case TOKEN_STATE_COMMA:
//             printf("%c \n", input[curr_pos]);
//             switch (input[curr_pos])
//             {
//             case '"':
//                 token_current_state = TOKEN_STATE_KEY;
//                 json_token_arr[curr_array_pos].type = TOKEN_TYPE_STRING;

//                 for (int i = curr_pos+1; input[i] != '"'; i++)
//                 {
//                     if (input[i] == '\n')
//                     {
//                         // raise error, as it should be in single line. will check and decide what to do later.
//                         return NULL;
//                     }
//                     counter++;
//                 }

//                 buffer = (char *)malloc(sizeof(char) * (counter + 1)); // +1 for '\0'

//                 strncpy(buffer, input + curr_pos + 1, counter);
//                 buffer[counter] = '\0';

//                 json_token_arr[curr_array_pos].value = buffer;

//                 // free(buffer);
//                 curr_array_pos++;
//                 curr_pos += counter;
//                 counter = 0;
//                 break;

//             case ' ':
//                 break;
            
//             default:
//                 printf("after comma their must be a key \n");
//                 break;
//             }

//         default:
//             break;
//         }
//         curr_pos++;
//     }

//     json_token_arr[curr_array_pos].type = TOKEN_TYPE_NONE;

//     print_tokenized_data(json_token_arr);

//     return json_token_arr;
// }

// static void print_tokenized_data(json_token *json_token_arr)
// {
//     for (int i = 0; json_token_arr[i].type != TOKEN_TYPE_NONE; i++)
//     {
//         printf("struct info of id: %d, type: %d, value: %s \n", i, json_token_arr[i].type, json_token_arr[i].value);
//     }
// }