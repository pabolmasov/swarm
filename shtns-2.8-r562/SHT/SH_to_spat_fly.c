// This file was automatically generated by 'make' from file 'fly_SH_to_spat.gen.c'.
// To modify it, please consider modifying fly_SH_to_spat.gen.c
/*
 * Copyright (c) 2010-2016 Centre National de la Recherche Scientifique.
 * written by Nathanael Schaeffer (CNRS, ISTerre, Grenoble, France).
 * 
 * nathanael.schaeffer@univ-grenoble-alpes.fr
 * 
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software. You can use,
 * modify and/or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 * 
 */


	static void GEN3(SH_to_spat_fly,NWAY,SUFFIX)(shtns_cfg shtns, cplx *Qlm, double *Vr, const long int llim) {
  #ifndef SHT_GRAD
  #else
  #endif

  #ifndef SHT_AXISYM
	v2d *BrF;
	#define qr(l) vall(creal(Ql[l]))
	#define qi(l) vall(cimag(Ql[l]))
	unsigned im, imlim;
  #else
	double* const BrF = Vr;
  #endif
	long int nk, k,l,m;
	double *alm, *al;
	s2d *ct, *st;
	double Ql0[llim+2];

  #ifndef SHT_AXISYM
	BrF = (v2d*) Vr;
	#ifdef _GCC_VEC_
	if (shtns->fftc_mode > 0) {		// alloc memory for the FFT
		unsigned long nv = shtns->nspat;
		BrF = (v2d*) VMALLOC( nv * sizeof(double) );
	}
	  #ifdef SHT_GRAD
	  #endif
	#else
	if (shtns->ncplx_fft > 0) {		// alloc memory for the FFT
		BrF = VMALLOC( shtns->ncplx_fft * sizeof(cplx) );
	}
	  #ifdef SHT_GRAD
	  #endif
	#endif
	imlim = MTR;
	#ifdef SHT_VAR_LTR
		if (imlim*MRES > (unsigned) llim) imlim = ((unsigned) llim)/MRES;		// 32bit mul and div should be faster
	#endif
  #else
	#ifdef SHT_GRAD
	#endif
  #endif

	ct = (s2d*) shtns->ct;		st = (s2d*) shtns->st;
	{	//	im=0;
		alm = shtns->alm;
 		l=1;
		Ql0[0] = (double) Qlm[0];		// l=0
		do {		// for m=0, compress the complex Q,S,T to double
			Ql0[l] = (double) Qlm[l];	//	Ql[l+1] = (double) Qlm[l+1];
			++l;
		} while(l<=llim);
		k=0;	nk = NLAT_2;
	#if _GCC_VEC_
		nk = ((unsigned)(nk+VSIZE2-1)) / VSIZE2;
	#endif
		do {
			l=0;	al = alm;
			rnd cost[NWAY], y0[NWAY], y1[NWAY];
			rnd re[NWAY], ro[NWAY];
			for (int j=0; j<NWAY; ++j) {
				cost[j] = vread(ct, j+k);
				y0[j] = vall(al[0]);
				re[j] = y0[j] * vall(Ql0[0]);
			}
			for (int j=0; j<NWAY; ++j) {
				y1[j]  = vall(al[0]*al[1]) * cost[j];
			}
			for (int j=0; j<NWAY; ++j) {
				ro[j] = y1[j] * vall(Ql0[1]);
			}
			al+=2;	l+=2;
			while(l<llim) {
				for (int j=0; j<NWAY; ++j) {
					y0[j]  = vall(al[1])*(cost[j]*y1[j]) + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					re[j] += y0[j] * vall(Ql0[l]);
				}
				for (int j=0; j<NWAY; ++j) {
					y1[j]  = vall(al[3])*(cost[j]*y0[j]) + vall(al[2])*y1[j];
				}
				for (int j=0; j<NWAY; ++j) {
					ro[j] += y1[j] * vall(Ql0[l+1]);
				}
				al+=4;	l+=2;
			}
			if (l==llim) {
				for (int j=0; j<NWAY; ++j) {
					y0[j]  = vall(al[1])*cost[j]*y1[j] + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					re[j] += y0[j] * vall(Ql0[l]);
				}
			}
		#ifndef SHTNS4MAGIC
			for (int j=0; j<NWAY; ++j) {
				S2D_STORE(BrF, j+k, re[j], ro[j])
			}
		#else
			for (int j=0; j<NWAY; ++j) {
				if ((k+j)>=nk) break;
				S2D_STORE_4MAGIC(BrF, j+k, re[j], ro[j])
			}
		#endif
			k+=NWAY;
		} while (k < nk);
	}

  #ifndef SHT_AXISYM
	#if _GCC_VEC_
		BrF += NLAT_2;
	#else
		BrF += NLAT;
	#endif
	for(im=1; im<=imlim; ++im) {
		m = im*MRES;
		//l = LiM(shtns, 0,im);
		l = (im*(2*(LMAX+1)-(m+MRES)))>>1;
		//alm = shtns->alm[im];
		//alm = shtns->alm[0] + im*(2*LMAX - (im-1)*MRES);        // for m > 0
		alm += 2*(LMAX+1-m+MRES);

		cplx* Ql = &Qlm[l];	// virtual pointer for l=0 and im

		k=0;	l=shtns->tm[im];
	#if _GCC_VEC_
		l>>=1;		// stay on a 16 byte boundary
		while (k<l) {	// polar optimization
	#ifndef SHTNS4MAGIC
			BrF[k] = vdup(0.0);				BrF[(NPHI-2*im)*NLAT_2 + k] = vdup(0.0);
			BrF[NLAT_2-l+k] = vdup(0.0);	BrF[(NPHI+1-2*im)*NLAT_2 -l+k] = vdup(0.0);
	#else
			BrF[2*k] = vdup(0.0);			BrF[(NPHI-2*im)*NLAT_2 + 2*k] = vdup(0.0);
			BrF[2*k+1] = vdup(0.0);			BrF[(NPHI-2*im)*NLAT_2 +2*k+1] = vdup(0.0);
	#endif
			++k;
		}
		k = ((unsigned) k) / (VSIZE2/2);
	#else
		while (k<l) {	// polar optimization
		  #ifndef SHTNS4MAGIC
			BrF[k] = 0.0;		BrF[NLAT-l+k] = 0.0;
		  #else
			BrF[2*k] = 0.0;		BrF[2*k+1] = 0.0;
		  #endif
			++k;
		}
	#endif
		do {
			al = alm;
			rnd cost[NWAY], y0[NWAY], y1[NWAY];
			rnd rer[NWAY], rei[NWAY], ror[NWAY], roi[NWAY];
			for (int j=0; j<NWAY; ++j) {
				cost[j] = vread(st, k+j);
				y0[j] = vall(1.0);
			}
			l=m;
			long int ny = 0;
		  if ((int)llim <= SHT_L_RESCALE_FLY) {
			do {		// sin(theta)^m
				if (l&1) for (int j=0; j<NWAY; ++j) y0[j] *= cost[j];
				for (int j=0; j<NWAY; ++j) cost[j] *= cost[j];
			} while(l >>= 1);
		  } else {
			long int nsint = 0;
			do {		// sin(theta)^m		(use rescaling to avoid underflow)
				if (l&1) {
					for (int j=NWAY-1; j>=0; --j) y0[j] *= cost[j];
					ny += nsint;
					if (vlo(y0[NWAY-1]) < (SHT_ACCURACY+1.0/SHT_SCALE_FACTOR)) {
						ny--;
						for (int j=NWAY-1; j>=0; --j) y0[j] *= vall(SHT_SCALE_FACTOR);
					}
				}
				for (int j=NWAY-1; j>=0; --j) cost[j] *= cost[j];
				nsint += nsint;
				if (vlo(cost[NWAY-1]) < 1.0/SHT_SCALE_FACTOR) {
					nsint--;
					for (int j=NWAY-1; j>=0; --j) cost[j] *= vall(SHT_SCALE_FACTOR);
				}
			} while(l >>= 1);
		  }
			for (int j=0; j<NWAY; ++j) {
				y0[j] *= vall(al[0]);
				cost[j] = vread(ct, j+k);
				ror[j] = vall(0.0);		roi[j] = vall(0.0);
				rer[j] = vall(0.0);		rei[j] = vall(0.0);
			}
			for (int j=0; j<NWAY; ++j) {
				y1[j]  = (vall(al[1])*y0[j]) *cost[j];		//	y1[j] = vall(al[1])*cost[j]*y0[j];
			}
			l=m;		al+=2;
			while ((ny<0) && (l<llim)) {		// ylm treated as zero and ignored if ny < 0
				for (int j=0; j<NWAY; ++j) {
					y0[j] = (vall(al[1])*cost[j])*y1[j] + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					y1[j] = (vall(al[3])*cost[j])*y0[j] + vall(al[2])*y1[j];
				}
				l+=2;	al+=4;
				if (fabs(vlo(y0[NWAY-1])) > SHT_ACCURACY*SHT_SCALE_FACTOR + 1.0) {		// rescale when value is significant
					++ny;
					for (int j=0; j<NWAY; ++j) {
						y0[j] *= vall(1.0/SHT_SCALE_FACTOR);		y1[j] *= vall(1.0/SHT_SCALE_FACTOR);
					}
				}
			}
		  if (ny == 0) {
			while (l<llim) {	// compute even and odd parts
				for (int j=0; j<NWAY; ++j) {	rer[j] += y0[j]  * qr(l);		rei[j] += y0[j] * qi(l);	}
				for (int j=0; j<NWAY; ++j) {
					y0[j] = vall(al[1])*(cost[j]*y1[j]) + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {	ror[j] += y1[j]  * qr(l+1);		roi[j] += y1[j] * qi(l+1);	}
				for (int j=0; j<NWAY; ++j) {
					y1[j] = vall(al[3])*(cost[j]*y0[j]) + vall(al[2])*y1[j];
				}
				l+=2;	al+=4;
			}
			if (l==llim) {
				for (int j=0; j<NWAY; ++j) {	rer[j] += y0[j]  * qr(l);		rei[j] += y0[j] * qi(l);	}
			}
		  }
		#ifndef SHTNS4MAGIC
			for (int j=0; j<NWAY; ++j) {
				S2D_CSTORE(BrF, k+j, rer[j], ror[j], rei[j], roi[j])
			}
		#else
			for (int j=0; j<NWAY; ++j) {
				if ((k+j)>=nk) break;
				S2D_CSTORE_4MAGIC(BrF, k+j, rer[j], ror[j], rei[j], roi[j])
			}
		#endif
			k+=NWAY;
		} while (k < nk);
	#if _GCC_VEC_
		BrF += NLAT_2;
	#else
		BrF += NLAT;
	#endif
	}

  #if _GCC_VEC_
	for (k=0; k < NLAT_2*(NPHI-1-2*imlim); ++k) {	// padding for high m's
		BrF[k] = vdup(0.0);
	}
	BrF -= NLAT_2*(imlim+1);		// restore original pointer
  #else
	for (k=0; k < NLAT*((NPHI>>1) -imlim); ++k) {	// padding for high m's
			BrF[k] = 0.0;
	}
	BrF -= NLAT*(imlim+1);		// restore original pointer
  #endif
    // NPHI > 1 as SHT_AXISYM is not defined.
	#if _GCC_VEC_
  	if (shtns->fftc_mode >= 0) {
		if (shtns->fftc_mode == 0) {
			fftw_execute_dft(shtns->ifftc, (cplx *) BrF, (cplx *) Vr);
		} else {		// split dft
			fftw_execute_split_dft(shtns->ifftc,((double*)BrF)+1, ((double*)BrF), Vr+NPHI, Vr);
			VFREE(BrF);
		}
	}
	#else
	if (shtns->ncplx_fft >= 0) {
		fftw_execute_dft_c2r(shtns->ifft, (cplx *) BrF, Vr);
		if (shtns->ncplx_fft > 0) {		// free memory
			VFREE(BrF);
		}
	}
	#endif
  #endif

	#undef qr
	#undef qi
  }

  #ifndef SHT_AXISYM

	static void GEN3(SH_m_to_spat_fly,NWAY,SUFFIX)(shtns_cfg shtns, int im, cplx *Qlm, cplx *Vr, const long int llim) {
  #ifndef SHT_GRAD
  #else
  #endif

	v2d *BrF;
	#define qr(l) vall(creal(Qlm[l]))
	#define qi(l) vall(cimag(Qlm[l]))
	long int nk, k,l,m;
	double *alm, *al;
	s2d *ct, *st;

	BrF = (v2d*) Vr;

	nk = NLAT_2;
	#if _GCC_VEC_
		nk = ((unsigned)(nk+VSIZE2-1)) / VSIZE2;
	#endif
	ct = (s2d*) shtns->ct;		st = (s2d*) shtns->st;

	if (im == 0) {
		double Ql0[llim+1];

		#ifdef SHT_GRAD
		#endif

 		l=1;
		alm = shtns->alm;
		Ql0[0] = (double) Qlm[0];		// l=0
		do {		// for m=0, compress the complex Q,S,T to double
			Ql0[l] = (double) Qlm[l];	//	Ql[l+1] = (double) Qlm[l+1];
			++l;
		} while(l<=llim);
		k=0;
		do {
			l=0;	al = alm;
			rnd cost[NWAY], y0[NWAY], y1[NWAY];
			rnd re[NWAY], ro[NWAY];
			for (int j=0; j<NWAY; ++j) {
				cost[j] = vread(ct, j+k);
				y0[j] = vall(al[0]);
				re[j] = y0[j] * vall(Ql0[0]);
			}
			for (int j=0; j<NWAY; ++j) {
				y1[j]  = vall(al[0]*al[1]) * cost[j];
			}
			for (int j=0; j<NWAY; ++j) {
				ro[j] = y1[j] * vall(Ql0[1]);
			}
			al+=2;	l+=2;
			while(l<llim) {
				for (int j=0; j<NWAY; ++j) {
					y0[j]  = vall(al[1])*(cost[j]*y1[j]) + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					re[j] += y0[j] * vall(Ql0[l]);
				}
				for (int j=0; j<NWAY; ++j) {
					y1[j]  = vall(al[3])*(cost[j]*y0[j]) + vall(al[2])*y1[j];
				}
				for (int j=0; j<NWAY; ++j) {
					ro[j] += y1[j] * vall(Ql0[l+1]);
				}
				al+=4;	l+=2;
			}
			if (l==llim) {
				for (int j=0; j<NWAY; ++j) {
					y0[j]  = vall(al[1])*cost[j]*y1[j] + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					re[j] += y0[j] * vall(Ql0[l]);
				}
			}
		#if _GCC_VEC_
			for (int j=0; j<NWAY; ++j) {
				S2D_CSTORE2(BrF, k+j, re[j], ro[j], vall(0), vall(0))
			}
		#else
			for (int j=0; j<NWAY; ++j) {
				BrF[k+j] = (re[j]+ro[j]);
				BrF[NLAT-k-1-j] = (re[j]-ro[j]);
			}
		#endif
			k+=NWAY;
		} while (k < nk);

	} else {	// im > 0
		m = im*MRES;
		l = im*(2*(LMAX+1) -m);		// to compute position in NLM array.
		alm = shtns->alm + l+m;
		Qlm -= m;	// virtual pointer for l=0


		k=0;	l=shtns->tm[im];
		while (k < l) {	// polar optimization
			BrF[k] = vdup(0.0);		BrF[NLAT-l+k] = vdup(0.0);
			++k;
		}
		k = ((unsigned) l) / VSIZE2;
		do {
			al = alm;
			rnd cost[NWAY], y0[NWAY], y1[NWAY];
			rnd rer[NWAY], rei[NWAY], ror[NWAY], roi[NWAY];
			for (int j=0; j<NWAY; ++j) {
				cost[j] = vread(st, k+j);
				y0[j] = vall(1.0);
			}
			l=m;
			long int ny = 0;
		  if ((int)llim <= SHT_L_RESCALE_FLY) {
			do {		// sin(theta)^m
				if (l&1) for (int j=0; j<NWAY; ++j) y0[j] *= cost[j];
				for (int j=0; j<NWAY; ++j) cost[j] *= cost[j];
			} while(l >>= 1);
		  } else {
			long int nsint = 0;
			do {		// sin(theta)^m		(use rescaling to avoid underflow)
				if (l&1) {
					for (int j=NWAY-1; j>=0; --j) y0[j] *= cost[j];
					ny += nsint;
					if (vlo(y0[NWAY-1]) < (SHT_ACCURACY+1.0/SHT_SCALE_FACTOR)) {
						ny--;
						for (int j=NWAY-1; j>=0; --j) y0[j] *= vall(SHT_SCALE_FACTOR);
					}
				}
				for (int j=NWAY-1; j>=0; --j) cost[j] *= cost[j];
				nsint += nsint;
				if (vlo(cost[NWAY-1]) < 1.0/SHT_SCALE_FACTOR) {
					nsint--;
					for (int j=NWAY-1; j>=0; --j) cost[j] *= vall(SHT_SCALE_FACTOR);
				}
			} while(l >>= 1);
		  }
			for (int j=0; j<NWAY; ++j) {
				y0[j] *= vall(al[0]);
				cost[j] = vread(ct, j+k);
				ror[j] = vall(0.0);		roi[j] = vall(0.0);
				rer[j] = vall(0.0);		rei[j] = vall(0.0);
			}
			for (int j=0; j<NWAY; ++j) {
				y1[j]  = (vall(al[1])*y0[j]) *cost[j];		//	y1[j] = vall(al[1])*cost[j]*y0[j];
			}
			l=m;		al+=2;
			while ((ny<0) && (l<llim)) {		// ylm treated as zero and ignored if ny < 0
				for (int j=0; j<NWAY; ++j) {
					y0[j] = (vall(al[1])*cost[j])*y1[j] + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					y1[j] = (vall(al[3])*cost[j])*y0[j] + vall(al[2])*y1[j];
				}
				l+=2;	al+=4;
				if (fabs(vlo(y0[NWAY-1])) > SHT_ACCURACY*SHT_SCALE_FACTOR + 1.0) {		// rescale when value is significant
					++ny;
					for (int j=0; j<NWAY; ++j) {
						y0[j] *= vall(1.0/SHT_SCALE_FACTOR);		y1[j] *= vall(1.0/SHT_SCALE_FACTOR);
					}
				}
			}
		  if (ny == 0) {
			while (l<llim) {	// compute even and odd parts
				for (int j=0; j<NWAY; ++j) {	rer[j] += y0[j]  * qr(l);		rei[j] += y0[j] * qi(l);	}
				for (int j=0; j<NWAY; ++j) {
					y0[j] = vall(al[1])*(cost[j]*y1[j]) + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {	ror[j] += y1[j]  * qr(l+1);		roi[j] += y1[j] * qi(l+1);	}
				for (int j=0; j<NWAY; ++j) {
					y1[j] = vall(al[3])*(cost[j]*y0[j]) + vall(al[2])*y1[j];
				}
				l+=2;	al+=4;
			}
			if (l==llim) {
				for (int j=0; j<NWAY; ++j) {	rer[j] += y0[j]  * qr(l);		rei[j] += y0[j] * qi(l);	}
			}
		  }
		#if _GCC_VEC_
			for (int j=0; j<NWAY; ++j) {
				S2D_CSTORE2(BrF, k+j, rer[j], ror[j], rei[j], roi[j])
			}
		#else
			for (int j=0; j<NWAY; ++j) {
				BrF[k+j] = (rer[j]+ror[j]) + I*(rei[j]+roi[j]);
				BrF[NLAT-k-1-j] = (rer[j]-ror[j]) + I*(rei[j]-roi[j]);
			}
		#endif
			k+=NWAY;
		} while (k < nk);
	}

	#undef qr
	#undef qi
  }

  #endif
