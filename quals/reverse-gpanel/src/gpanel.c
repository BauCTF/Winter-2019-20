/*
Copyright 2018 Google LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char HEADER[] =
    "/===========================================================================\\\n"
    "|                              W3lc0m3 t0 GP@n3l                            |\n"
    "|                               H@ked By _($&&@                             |\n"
    "+===========================================================================+\n";

const char ACCESS_DENIED[] = "ACCESS DENIED\n";

const useconds_t delay_per_char = 10000;

void text_animation(const char *txt)
{
    while (*txt)
    {
        putchar(*txt++);
        fflush(NULL);
        usleep(delay_per_char);
    }
}

void verify_animation(unsigned n_cycles)
{
    const char states[] = {'/', '-', '\\', '|'};
    for (unsigned i = 0; i < n_cycles; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int s = 0; s < sizeof(states); s++)
            {
                putchar(states[s]);
                putchar('\b');
                fflush(NULL);
                usleep(delay_per_char * 10);
            }
        }
        putchar('.');
    }
}

int main(int argc, char *argv[])
{
    text_animation(HEADER);
    if (argc != 3)
    {
        printf("[ERROR] Login information missing\n");
        printf("Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }
    else
    {
        text_animation(" ~> Verifying.");
        verify_animation(3);
        if (strcmp(argv[1], "BaD_gUy"))
        {
            text_animation("\nTitle: \nA Discovrse of Fire and Salt (A Discourse of Fire and Salt)");
            text_animation("\nPYTHAGORAS who of all Pagans was undoubtedly,\nby common consent and approbation,\nheld to have made more profound search,\nand with less incertainty penetrated into the secrets as well of Divinity,\nas of Nature, having quaffed full draughts from the living source of Mosaicall Traditions,\namid’st his darke sentences, where, according to the Letter, he touched one thing,\nand mystically understood and comprised another;\n(wherein he imitates the Ægyptians and Chaldæans, or rather, the Hebrewes, from whence all theirs proceeded)\nhe here sets downe these two: Not to speake of God without Light;\nand to apply Salt in all his Sacrifices and Offerings;\nwhich he borrowed word for word from Moses, as we shall hereafter declare. \nFor our intention is here to Treat of Fire and of Salt.");
            putchar('\n');
            text_animation(ACCESS_DENIED);
            text_animation(" ~> Incorrect username\n");
            return 1;
        }

        char *buffer = (char *)malloc(strlen(argv[2]) + 1);
        strcpy(buffer, argv[2]);
        // for (size_t i = 0; i<strlen(buffer)>> 1; i++)
        // {
        //     char c = buffer[i];
        //     buffer[i] = buffer[strlen(buffer) - i - 1];
        //     buffer[strlen(buffer) - i - 1] = c;
        // }

        verify_animation(3);
        if (!strcmp(buffer, "evvxhonx0fuc"))
        {
            text_animation("Correct!\n");
            text_animation("Welcome back!\n");
            char local_buf[128];
            snprintf(local_buf, sizeof(local_buf), "CTF{%s}\n", argv[2]);
            text_animation(local_buf);
            text_animation("ENCRYPT3D WITH LOVE <3 \n");
        }
        else
        {
            text_animation("\nIn the beginning God created Heaven and Earth;\nthis said Moses on the entrance upon Genesis. Whereupon the Jew Aristobulus,\nand some Ethniques willing to shew that Pythagoras and Plato had read Moses bookes, and from thence drawne the greatest part of their most secret Philosophy,\nalledged that which Moses should have said, that the heaven and the earth were first created;\nPlato in his Timæus, after, Timæus Locrien said that God first assembled Fire and Earth, to build an universe thereof;\n(we will shew it more sensibly of Zohar in the Weik of a Candle lighted, for all consists of light, being the first of all Creatures.)\nThese Philosophers presupposing that the World consisted (as indeed it doth) of the foure Elements, which are as well in heaven,\nand yet higher, as in the earth, and lower, but in a diverse manner.\n");
            text_animation(ACCESS_DENIED);
            text_animation(" ~> Incorrect password\n");
        }
    }

    return 0;
}
