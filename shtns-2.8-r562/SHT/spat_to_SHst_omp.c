// This file was automatically generated by 'make' from file 'omp_spat_to_SH.gen.c'.
// To modify it, please consider modifying omp_spat_to_SH.gen.c
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

//////////////////////////////////////////////////

	static
	void GEN3(_an2,NWAY,SUFFIX)(shtns_cfg shtns, double *BtF, double *BpF, cplx *Slm, cplx *Tlm, const long int llim, const int imlim) {

	double *alm, *al;
	double *wg, *ct, *st;
	double *l_2;
	long int nk, k, l,m;
	int k_inc, m_inc;
	unsigned m0, mstep;
  #ifndef SHT_AXISYM
	unsigned im;
  #endif
	rnd vw[4*llim+8];

	double ter[NLAT_2 + NWAY*VSIZE2] SSE;
	double tor[NLAT_2 + NWAY*VSIZE2] SSE;
	double per[NLAT_2 + NWAY*VSIZE2] SSE;
	double por[NLAT_2 + NWAY*VSIZE2] SSE;
  #ifndef SHT_AXISYM
	double tei[NLAT_2 + NWAY*VSIZE2] SSE;
	double toi[NLAT_2 + NWAY*VSIZE2] SSE;
	double pei[NLAT_2 + NWAY*VSIZE2] SSE;
	double poi[NLAT_2 + NWAY*VSIZE2] SSE;
  #endif

	// ACCESS PATTERN
	k_inc = shtns->k_stride_a;
	m_inc = shtns->m_stride_a;

	nk = NLAT_2;	// copy NLAT_2 to a local variable for faster access (inner loop limit)
	#if _GCC_VEC_
	  nk = ((unsigned) nk+(VSIZE2-1))/VSIZE2;
	#endif
	wg = shtns->wg;		ct = shtns->ct;		st = shtns->st;
	l_2 = shtns->l_2;
	for (k=nk*VSIZE2; k<(nk-1+NWAY)*VSIZE2; ++k) {		// never written, so this is now done for all m's
		ter[k] = 0.0;		tor[k] = 0.0;
		per[k] = 0.0;		por[k] = 0.0;
	  #ifndef SHT_AXISYM
		tei[k] = 0.0;		toi[k] = 0.0;
		pei[k] = 0.0;		poi[k] = 0.0;
	  #endif
	}

	#ifndef _OPENMP
		m0 = 0;		mstep = 1;
	#else
		m0 = omp_get_thread_num();
		mstep = omp_get_num_threads();
		if (m0 == 0)
	#endif
	{		// im=0 : dzl.p = 0.0 and evrything is REAL
		alm = shtns->blm;
		// compute symmetric and antisymmetric parts. (do not weight here, it is cheaper to weight y0)
		SYM_ASYM_M0_V(BtF, ter, tor)
		SYM_ASYM_M0_V(BpF, per, por)
		Slm[0] = 0.0;		Tlm[0] = 0.0;		// l=0 is zero for the vector transform.
		k = 0;
		for (l=0;l<llim;++l) {
			vw[2*l] = vall(0.0);		vw[2*l+1] = vall(0.0);
		}
		do {
			al = alm;
			rnd cost[NWAY], y0[NWAY], y1[NWAY];
			rnd sint[NWAY], dy0[NWAY], dy1[NWAY];
			rnd terk[NWAY], tork[NWAY], perk[NWAY], pork[NWAY];
			for (int j=0; j<NWAY; ++j) {
				cost[j] = vread(ct, k+j);
				y0[j] = vall(al[0]) * vread(wg, k+j);		// weight of Gauss quadrature appears here
				dy0[j] = vall(0.0);
				sint[j] = -vread(st, k+j);
				y1[j] =  (vall(al[1])*y0[j]) * cost[j];
				dy1[j] = (vall(al[1])*y0[j]) * sint[j];
				terk[j] = vread(ter, k+j);		tork[j] = vread(tor, k+j);
				perk[j] = vread(per, k+j);		pork[j] = vread(por, k+j);
			}
			al+=2;	l=1;
			while(l<llim) {
				for (int j=0; j<NWAY; ++j) {
					dy0[j] = vall(al[1])*(cost[j]*dy1[j] + y1[j]*sint[j]) + vall(al[0])*dy0[j];
					y0[j]  = vall(al[1])*(cost[j]*y1[j]) + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					vw[2*l-2] += dy1[j] * terk[j];
					vw[2*l-1] -= dy1[j] * perk[j];
				}
				for (int j=0; j<NWAY; ++j) {
					dy1[j] = vall(al[3])*(cost[j]*dy0[j] + y0[j]*sint[j]) + vall(al[2])*dy1[j];
					y1[j]  = vall(al[3])*(cost[j]*y0[j]) + vall(al[2])*y1[j];
				}
				for (int j=0; j<NWAY; ++j) {
					vw[2*l]   += dy0[j] * tork[j];
					vw[2*l+1] -= dy0[j] * pork[j];
				}
				al+=4;	l+=2;
			}
			if (l==llim) {
				for (int j=0; j<NWAY; ++j) {
					vw[2*l-2] += dy1[j] * terk[j];
					vw[2*l-1] -= dy1[j] * perk[j];
				}
			}
			k+=NWAY;
		} while (k < nk);
		for (l=1; l<=llim; ++l) {
			#if _GCC_VEC_
				((v2d*)Slm)[l] = v2d_reduce(vw[2*l-2], vall(0)) * vdup(l_2[l]);
				((v2d*)Tlm)[l] = v2d_reduce(vw[2*l-1], vall(0)) * vdup(l_2[l]);
			#else
				Slm[l] = vw[2*l-2]*l_2[l];		Tlm[l] = vw[2*l-1]*l_2[l];
			#endif
		}
		#ifdef SHT_VAR_LTR
			for (l=llim+1; l<= LMAX; ++l) {
				((v2d*)Slm)[l] = vdup(0.0);		((v2d*)Tlm)[l] = vdup(0.0);
			}
			#ifndef SHT_AXISYM
			if (imlim <= MMAX) {		// zero out m >= imlim
				l = LiM(shtns, imlim*MRES, imlim);
				do {
					((v2d*)Slm)[l] = vdup(0.0);		((v2d*)Tlm)[l] = vdup(0.0);
				} while(++l < shtns->nlm);
			}
			#endif
		#endif
		m0=mstep;
	}

  #ifndef SHT_AXISYM
	for (im=m0; im<imlim; im+=mstep) {
		m = im*MRES;
		l = shtns->tm[im] / VSIZE2;
		//alm = shtns->blm[im];
		alm = shtns->blm + im*(2*(LMAX+1) -m+MRES);
		// compute symmetric and anti-symmetric parts:
		SYM_ASYM_V(BtF, ter, tor, tei, toi, l)
		SYM_ASYM_V(BpF, per, por, pei, poi, l)
		k=l;
		#if _GCC_VEC_
			rnd* v = vw;
		#else
			double* v = (double *) vw;
		#endif
		for (l=llim+1-m; l>=0; l--) {
			v[0] = vall(0.0);		v[1] = vall(0.0);
			v[2] = vall(0.0);		v[3] = vall(0.0);		v+=4;
		}
		do {
		#if _GCC_VEC_
			rnd* v = vw;
		#else
			double* v = (double *) vw;
		#endif
			al = alm;
			rnd cost[NWAY], y0[NWAY], y1[NWAY];
			rnd st2[NWAY], dy0[NWAY], dy1[NWAY];
			rnd terk[NWAY], teik[NWAY], tork[NWAY], toik[NWAY];
			rnd perk[NWAY], peik[NWAY], pork[NWAY], poik[NWAY];
			for (int j=0; j<NWAY; ++j) {
				cost[j] = vread(st, k+j);
				y0[j] = vall(0.5);
			}
			l=m-1;
			long int ny = 0;	// exponent to extend double precision range.
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
				cost[j] = vread(ct, k+j);
				y1[j]  = (vall(al[1])*y0[j]) *cost[j];
			}
			l=m;	al+=2;
			while ((ny<0) && (l<llim)) {		// ylm treated as zero and ignored if ny < 0
				for (int j=0; j<NWAY; ++j) {
					y0[j] = vall(al[1])*(cost[j]*y1[j]) + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					y1[j] = vall(al[3])*(cost[j]*y0[j]) + vall(al[2])*y1[j];
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
			v+=4*(l-m);
			for (int j=0; j<NWAY; ++j) {	// prefetch
				y0[j] *= vread(wg, k+j);		y1[j] *= vread(wg, k+j);		// weight appears here (must be after the previous accuracy loop).
				terk[j] = vread( ter, k+j);		teik[j] = vread( tei, k+j);		tork[j] = vread( tor, k+j);		toik[j] = vread( toi, k+j);
				perk[j] = vread( per, k+j);		peik[j] = vread( pei, k+j);		pork[j] = vread( por, k+j);		poik[j] = vread( poi, k+j);
			}
			while (l<llim) {	// compute even and odd parts
				for (int j=0; j<NWAY; ++j)	{	v[0] += y0[j] * terk[j];	v[1] += y0[j] * teik[j];	}
				for (int j=0; j<NWAY; ++j)	{	v[2] += y0[j] * perk[j];	v[3] += y0[j] * peik[j];	}
				for (int j=0; j<NWAY; ++j) {
					y0[j] = vall(al[1])*(cost[j]*y1[j]) + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j)	{	v[4] += y1[j] * tork[j];	v[5] += y1[j] * toik[j];	}
				for (int j=0; j<NWAY; ++j)	{	v[6] += y1[j] * pork[j];	v[7] += y1[j] * poik[j];	}
				v+=8;
				for (int j=0; j<NWAY; ++j) {
					y1[j] = vall(al[3])*(cost[j]*y0[j]) + vall(al[2])*y1[j];
				}
				l+=2;	al+=4;
			}
				for (int j=0; j<NWAY; ++j)	{	v[0] += y0[j] * terk[j];	v[1] += y0[j] * teik[j];	}
				for (int j=0; j<NWAY; ++j)	{	v[2] += y0[j] * perk[j];	v[3] += y0[j] * peik[j];	}
			if (l==llim) {
				for (int j=0; j<NWAY; ++j)	{	v[4] += y1[j] * tork[j];	v[5] += y1[j] * toik[j];	}
				for (int j=0; j<NWAY; ++j)	{	v[6] += y1[j] * pork[j];	v[7] += y1[j] * poik[j];	}
			}
		  }
			k+=NWAY;
		} while (k < nk);
		l = LiM(shtns, m, im);
		v2d * const Sl = (v2d*) &Slm[l];
		v2d * const Tl = (v2d*) &Tlm[l];

		{	// convert from the two scalar SH to vector SH
			// Slm = - (I*m*Wlm + MX*Vlm) / (l*(l+1))		=> why does this work ??? (aliasing of 1/sin(theta) ???)
			// Tlm = - (I*m*Vlm - MX*Wlm) / (l*(l+1))
			double* mx = shtns->mx_van + 2*LM(shtns,m,m);	//(im*(2*(LMAX+1)-(m+MRES))) + 2*m;
			s2d em = vdup(m);
			v2d vl = v2d_reduce(vw[0], vw[1]);
			v2d wl = v2d_reduce(vw[2], vw[3]);
			v2d sl = vdup( 0.0 );
			v2d tl = vdup( 0.0 );
			for (int l=0; l<=llim-m; l++) {
				s2d mxu = vdup( mx[2*l] );
				s2d mxl = vdup( mx[2*l+1] );		// mxl for next iteration
				sl = addi( sl ,  em*wl );
				tl = addi( tl ,  em*vl );
				v2d sl1 =  mxl*vl;			// vs for next iter
				v2d tl1 = -mxl*wl;			// wt for next iter
				vl = v2d_reduce(vw[4*l+4], vw[4*l+5]);		// kept for next iteration
				wl = v2d_reduce(vw[4*l+6], vw[4*l+7]);
				sl += mxu*vl;
				tl -= mxu*wl;
				Sl[l] = -sl * vdup(l_2[l+m]);
				Tl[l] = -tl * vdup(l_2[l+m]);
				sl = sl1;
				tl = tl1;
			}
		}

		#ifdef SHT_VAR_LTR
			for (l=llim+1-m; l<=LMAX-m; ++l) {
				Sl[l] = vdup(0.0);		Tl[l] = vdup(0.0);
			}
		#endif
	}
  #endif
  }


	static void GEN3(spat_to_SHsphtor_omp,NWAY,SUFFIX)(shtns_cfg shtns, double *Vt, double *Vp, cplx *Slm, cplx *Tlm, long int llim) {

	double *BtF, *BpF;	// contains the Fourier transformed data
	unsigned imlim=0;

	BtF = Vt;	BpF = Vp;
  #ifndef SHT_AXISYM
	imlim = MTR;
	#ifdef SHT_VAR_LTR
		if (imlim*MRES > (unsigned) llim) imlim = ((unsigned) llim)/MRES;		// 32bit mul and div should be faster
	#endif
	if (shtns->fftc_mode >= 0) {
	    if (shtns->fftc_mode == 0) {	// in-place
		  #ifdef HAVE_LIBFFTW3_OMP
			fftw_execute_dft(shtns->fftc,(cplx*)BtF, (cplx*)BtF);
			fftw_execute_dft(shtns->fftc,(cplx*)BpF, (cplx*)BpF);
		  #endif
		} else {	// alloc memory for the transpose FFT
			unsigned long nv = shtns->nspat;
			BtF = (double*) VMALLOC( 2*nv * sizeof(double) );
			BpF = BtF + nv;
		  #ifdef HAVE_LIBFFTW3_OMP
			fftw_execute_split_dft(shtns->fftc, Vt+NPHI, Vt, BtF+1, BtF);
			fftw_execute_split_dft(shtns->fftc, Vp+NPHI, Vp, BpF+1, BpF);
		  #endif
	    }
	}
  #endif
	imlim += 1;

  #pragma omp parallel num_threads(shtns->nthreads)
  {
	#ifndef SHT_AXISYM
	#ifndef HAVE_LIBFFTW3_OMP
		if (shtns->fftc_mode == 0) {	// in-place
			#pragma omp single nowait
			fftw_execute_dft(shtns->fftc,(cplx*)BtF, (cplx*)BtF);
			#pragma omp single nowait
			fftw_execute_dft(shtns->fftc,(cplx*)BpF, (cplx*)BpF);
		} else if (shtns->fftc_mode > 0) {	// split out-of-place
			#pragma omp single nowait
			fftw_execute_split_dft(shtns->fftc, Vt+NPHI, Vt, ((double*)BtF)+1, ((double*)BtF));
			#pragma omp single nowait
			fftw_execute_split_dft(shtns->fftc, Vp+NPHI, Vp, ((double*)BpF)+1, ((double*)BpF));
		}
		#pragma omp barrier
	#endif
	#endif
	GEN3(_an2,NWAY,SUFFIX)(shtns, BtF, BpF, Slm, Tlm, llim, imlim);
  }

  #ifndef SHT_AXISYM
  	if (shtns->fftc_mode > 0) {		// free memory
	    VFREE(BtF);	// this frees also BpF.
	}
  #endif

  }