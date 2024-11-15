#include "main.h"

void init_nintendo_urls(URLs *urls) {
    const char* nintendo_base_url = "nintendo.net";
    const char* nintendo_account_url = "account";
    const char* nintendo_nasc_url = "nasc";
    const char* nintendo_discovery_url = "discovery.olv";

    snprintf(urls->url_1, sizeof(urls->url_1), "%s.%s", nintendo_account_url, nintendo_base_url);
    snprintf(urls->url_2, sizeof(urls->url_2), "%s.%s", nintendo_nasc_url, nintendo_base_url);
    snprintf(urls->url_3, sizeof(urls->url_3), "%s.%s", nintendo_discovery_url, nintendo_base_url);
}

void init_retendo_urls(URLs *urls) {
    const char* retendo_base_url = "retendo.online";
    const char* retendo_account_url = "account";
    const char* retendo_nasc_url = "nasc";
    const char* innoverse_discovery_url = "discovery.olv.innoverse.club";

    snprintf(urls->url_1, sizeof(urls->url_1), "%s.%s", retendo_account_url, retendo_base_url);
    snprintf(urls->url_2, sizeof(urls->url_2), "%s.%s", retendo_nasc_url, retendo_base_url);
    snprintf(urls->url_3, sizeof(urls->url_3), "%s", innoverse_discovery_url);
}

void display_urls(URLs *urls) {
    printf("Nintendo Network\n");
    printf("Retendo Network\n");
}

void switch_urls(URLs *urls, u32 keys) {
    if (keys & KEY_A) {
        init_nintendo_urls(urls);
    } else if (keys & KEY_X) {
        init_retendo_urls(urls);
    }
}

int main(int argc, char *argv[]) {
    gfxInitDefault();

    ndmuInit();
	hidInit();
	aptInit();
	frdInit();
	frdaInit();
	actaInit();

    consoleInit(GFX_TOP, NULL);

    URLs current_urls;
    init_nintendo_urls(&current_urls);

    display_urls(&current_urls);

    printf("Welcome to Retendo Patcher for 3DS !");
    printf("Press A to use Nintendo Server.");
    printf("Press X to use Retendo Server.");
    printf("Press START to exit the app.");

    while (aptMainLoop()) {
        hidScanInput();
        u32 keys = hidKeysDown();

        // Press START for exit the app
        if (keys & KEY_START) {
            break;
        }

        switch_urls(&current_urls, keys);

        display_urls(&current_urls);

        gfxFlushBuffers();
        gfxSwapBuffers();
    }

    actaExit();
	frdaExit();
	frdExit();
	aptExit();
	hidExit();
	ndmuExit();
    gfxExit();

    return 0;
}