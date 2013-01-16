#pragma once

int base64_pton(char const *src, uint8_t *target, size_t targsize);
int base64_ntop(uint8_t const *src, size_t srclength, char *target, size_t targsize) ;