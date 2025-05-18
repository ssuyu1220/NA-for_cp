#include <string.h>
#include <ctype.h>
#include <lber.h>
#include <ldap.h>
#include <slap.h>

int check_password(const char *pPasswd, struct berval *pErrmsg, Entry *pEntry, struct berval *pArg) {
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    size_t len = strlen(pPasswd);

    if (len < 8) {
        ber_str2bv("Password must be at least 8 characters long", 0, 0, pErrmsg);
        return 1;
    }

    for (size_t i = 0; i < len; ++i) {
        if (isupper((unsigned char)pPasswd[i])) has_upper = 1;
        else if (islower((unsigned char)pPasswd[i])) has_lower = 1;
        else if (isdigit((unsigned char)pPasswd[i])) has_digit = 1;
        else has_special = 1;
    }

    int classes = has_upper + has_lower + has_digit + has_special;
    if (classes < 3) {
        ber_str2bv("Password must include at least 3 of: upper, lower, digit, special characters", 0, 0, pErrmsg);
        return 1;
    }

    return 0;
}
