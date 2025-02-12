/*
    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2012 Lina Kulakova

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fmpz.h"
#include "fmpz_vec.h"
#include "fmpz_mod.h"
#include "fmpz_mod_poly.h"
#include "fmpz_mod_poly_factor.h"

int
_fmpz_mod_poly_is_squarefree_f(fmpz_t fac, const fmpz * f, slong len, const fmpz_mod_ctx_t ctx)
{
    fmpz * fd, * g;
    fmpz_t invd;
    slong dlen;
    int res = 0;

    if (len <= 2)
        return len != 0;

    fd = _fmpz_vec_init(2 * (len - 1));
    g = fd + len - 1;

    _fmpz_mod_poly_derivative(fd, f, len, ctx);
    dlen = len - 1;
    FMPZ_VEC_NORM(fd, dlen);

    if (dlen)
    {
        fmpz_init(invd);
        fmpz_gcdinv(fac, invd, fd + dlen - 1, fmpz_mod_ctx_modulus(ctx));
        if (fmpz_is_one(fac))
           res = (_fmpz_mod_poly_gcd_euclidean_f(fac, g, f, len, fd, dlen, ctx) == 1);
        fmpz_clear(invd);
    }
    /* else gcd(f, 0) = f, and len(f) > 2 */

    _fmpz_vec_clear(fd, 2 * (len - 1));
    return res;
}

int fmpz_mod_poly_is_squarefree_f(fmpz_t fac, const fmpz_mod_poly_t f,
                                                      const fmpz_mod_ctx_t ctx)
{
        return _fmpz_mod_poly_is_squarefree_f(fac, f->coeffs, f->length, ctx);
}
