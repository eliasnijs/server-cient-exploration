///////////////////////////////////////////////////////////
//// NOTE(Elias): Float Constant Functions

internal F32 
inf_F32(void)
{
  union{ F32 f; U32 u; } r;
  r.u = 0x7f800000;
  return(r.f);
}
internal F32 
neg_inf_F32(void)
{
  union{ F32 f; U32 u; } r;
  r.u = 0xff800000;
  return(r.f);
}

internal F64 
inf_F64(void)
{
  union{ F64 f; U64 u; } r;
  r.u = 0x7ff00000ff800000;
  return(r.f);
}

internal F64 
neg_inf_F64(void)
{
  union{ F64 f; U64 u; } r;
  r.u = 0xfff00000ff800000;
  return(r.f);
}

///////////////////////////////////////////////////////////
//// NOTE(Elias): Math functions 

internal F32 
abs_F32(F32 x)
{
  union{ F32 f; U32 u; } r;
  r.f = x;
  r.u = r.u & 0x7fffffff;
  return(r.f);
}

internal F64 
abs_F64(F64 x)
{
  union{ F32 f; U32 u; } r;
  r.f = x;
  r.u = r.u & 0x7fffffffffffffff;
  return(r.f);
} 

internal F32 
srqt_F32(F32 x)
{
  return(sqrtf(x));
}

internal F32 
sin_F32(F32 x)
{
  return(sinf(x));
}

internal F32 
cos_F32(F32 x)
{
  return(cosf(x));
}

internal F32 
tan_F32(F32 x)
{
  return(tanf(x));
}

internal F32 
ln_F32(F32 x)
{
  return(logf(x));
}

internal F64 
srqt_F64(F64 x)
{
  return(sqrt(x));
}

internal F64 
sin_F64(F64 x)
{
  return(sin(x));
}

internal F64 
cos_F64(F64 x)
{
  return(cos(x));
}

internal F64a 
tan_F64(F64 x)
{
  return(tan(x));
} 

internal F64 
ln_F64(F64 x)
{
  return(log(x));
} 

internal F32 
lerp(F32 a, F32 t, F32 b)
{
  F32 x = a + t*(b - a);
  return(x);
}

internal F32 
unlerp(F32 a, F32 x, F32 b)
{
  F32 t = 0.f;
  if (a != b)
  {
    t = (x - a) / (b - a);
  }
  return(t);
}
