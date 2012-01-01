/*
(Absolute) addresses to patch. You are looking for something like...

01BAA928   $- FF25 70B7E801 JMP DWORD PTR DS:[<&xlive.#1082>]
01BAA92E   $- FF25 6CB7E801 JMP DWORD PTR DS:[<&xlive.#5331>]
01BAA934   $- FF25 68B7E801 JMP DWORD PTR DS:[<&xlive.#5261>]
01BAA93A   $- FF25 64B7E801 JMP DWORD PTR DS:[<&xlive.#5267>]
 */

PATCH(0x01baac22, XLiveUnprotectData);
PATCH(0x01baac16, XLiveInitializeEx);
