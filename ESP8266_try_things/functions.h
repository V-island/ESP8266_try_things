#ifndef functions_h
#define functions_h

#include "Arduino.h"

// ===== LANGUAGE STRING FUNCTIONS ===== //

// for reading Strings from the PROGMEM
String str(const char* ptr) {
  char keyword[strlen_P(ptr)];

  strcpy_P(keyword, ptr);
  return String(keyword);
}

// for converting keywords
String keyword(const char* keywordPtr) {
  char keyword[strlen_P(keywordPtr)];

  strcpy_P(keyword, keywordPtr);

  String  str = "";
  uint8_t len = strlen(keyword);
  uint8_t i   = 0;

  while (i < len && keyword[i] != SLASH && keyword[i] != COMMA) {
    str += keyword[i];
    i++;
  }

  return str;
}

// equals function
bool eqls(const char* str, const char* keywordPtr) {
  if (strlen(str) > 255) return false;  // when string too long

  char keyword[strlen_P(keywordPtr) + 1];
  strcpy_P(keyword, keywordPtr);

  uint8_t lenStr     = strlen(str);
  uint8_t lenKeyword = strlen(keyword);

  if (lenStr > lenKeyword) return false;  // string can't be longer than keyword (but can be smaller because of '/'

  // and ',')

  uint8_t a      = 0;
  uint8_t b      = 0;
  bool    result = true;

  while (a < lenStr && b < lenKeyword) {
    if ((keyword[b] == SLASH) || (keyword[b] == COMMA)) b++;

    if (tolower(str[a]) != tolower(keyword[b])) result = false;

    if (((a == lenStr) && !result) || !result) { // fast forward to next comma
      while (b < lenKeyword && keyword[b] != COMMA) b++;
      result = true;
      a      = 0;
    } else {
      a++;
      b++;
    }
  }
  // comparison correct AND string checked until the end AND keyword checked until the end
  return result && a == lenStr && (keyword[b] == COMMA || keyword[b] == SLASH || keyword[b] == ENDOFLINE);
}

bool eqls(String str, const char* keywordPtr) {
  return eqls(str.c_str(), keywordPtr);
}

// boolean to string
String b2s(bool input) {
  return str(input ? STR_TRUE : STR_FALSE);
}

// boolean to asterix *
String b2a(bool input) {
  return input ? String(ASTERIX) : String(SPACE);
}

// string to boolean
bool s2b(String input) {
  return eqls(input, STR_TRUE);
}

// ===== PRINT FUNCTIONS ===== //
void prnt(const String s) {
  Serial.print(s);
}

void prnt(const bool b) {
  Serial.print(b2s(b));
}

void prnt(const char c) {
  Serial.print(c);
}

void prnt(const char* ptr) {
  Serial.print(FPSTR(ptr));
}

void prnt(const char* ptr, int len) {
  for (int i = 0; i < len; i++) prnt(ptr[i]);
}

void prnt(const int i) {
  Serial.print((String)i);
}

void prnt(const uint32_t i) {
  Serial.printf("%u", i);
}

void prntln() {
  Serial.println();
}

void prntln(const String s) {
  Serial.println(s);
}

void prntln(const bool b) {
  Serial.println(b2s(b));
}

void prntln(const char c) {
  Serial.println(c);
}

void prntln(const char* ptr) {
  Serial.println(FPSTR(ptr));
}

void prntln(const char* ptr, int len) {
  for (int i = 0; i < len; i++) prnt(ptr[i]);
  prntln();
}

void prntln(const int i) {
  Serial.println((String)i);
}

void prntln(const uint32_t i) {
  Serial.printf("%u\r\n", i);
}

#endif // ifndef functions_h
