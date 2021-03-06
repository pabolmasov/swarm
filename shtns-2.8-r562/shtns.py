# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.12
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

"""Python/NumPy interface to the SHTns spherical harmonic transform library"""


from sys import version_info as _swig_python_version_info
if _swig_python_version_info >= (2, 7, 0):
    def swig_import_helper():
        import importlib
        pkg = __name__.rpartition('.')[0]
        mname = '.'.join((pkg, '_shtns')).lstrip('.')
        try:
            return importlib.import_module(mname)
        except ImportError:
            return importlib.import_module('_shtns')
    _shtns = swig_import_helper()
    del swig_import_helper
elif _swig_python_version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_shtns', [dirname(__file__)])
        except ImportError:
            import _shtns
            return _shtns
        try:
            _mod = imp.load_module('_shtns', fp, pathname, description)
        finally:
            if fp is not None:
                fp.close()
        return _mod
    _shtns = swig_import_helper()
    del swig_import_helper
else:
    import _shtns
del _swig_python_version_info

try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr(self, class_type, name):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    raise AttributeError("'%s' object has no attribute '%s'" % (class_type.__name__, name))


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except __builtin__.Exception:
    class _object:
        pass
    _newclass = 0


import numpy as np

sht_orthonormal = _shtns.sht_orthonormal
sht_fourpi = _shtns.sht_fourpi
sht_schmidt = _shtns.sht_schmidt
SHT_NO_CS_PHASE = _shtns.SHT_NO_CS_PHASE
SHT_REAL_NORM = _shtns.SHT_REAL_NORM
sht_gauss = _shtns.sht_gauss
sht_auto = _shtns.sht_auto
sht_reg_fast = _shtns.sht_reg_fast
sht_reg_dct = _shtns.sht_reg_dct
sht_quick_init = _shtns.sht_quick_init
sht_reg_poles = _shtns.sht_reg_poles
sht_gauss_fly = _shtns.sht_gauss_fly
SHT_THETA_CONTIGUOUS = _shtns.SHT_THETA_CONTIGUOUS
SHT_PHI_CONTIGUOUS = _shtns.SHT_PHI_CONTIGUOUS
SHT_SOUTH_POLE_FIRST = _shtns.SHT_SOUTH_POLE_FIRST
SHT_SCALAR_ONLY = _shtns.SHT_SCALAR_ONLY
SHT_LOAD_SAVE_CFG = _shtns.SHT_LOAD_SAVE_CFG
class sht(_object):
    """Proxy of C shtns_info struct."""

    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, sht, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, sht, name)
    __repr__ = _swig_repr
    __swig_getmethods__["nlm"] = _shtns.sht_nlm_get
    if _newclass:
        nlm = _swig_property(_shtns.sht_nlm_get)
    __swig_getmethods__["lmax"] = _shtns.sht_lmax_get
    if _newclass:
        lmax = _swig_property(_shtns.sht_lmax_get)
    __swig_getmethods__["mmax"] = _shtns.sht_mmax_get
    if _newclass:
        mmax = _swig_property(_shtns.sht_mmax_get)
    __swig_getmethods__["mres"] = _shtns.sht_mres_get
    if _newclass:
        mres = _swig_property(_shtns.sht_mres_get)
    __swig_getmethods__["nphi"] = _shtns.sht_nphi_get
    if _newclass:
        nphi = _swig_property(_shtns.sht_nphi_get)
    __swig_getmethods__["nlat"] = _shtns.sht_nlat_get
    if _newclass:
        nlat = _swig_property(_shtns.sht_nlat_get)
    __swig_getmethods__["nspat"] = _shtns.sht_nspat_get
    if _newclass:
        nspat = _swig_property(_shtns.sht_nspat_get)

    def __init__(self, lmax, mmax=-1, mres=1, norm=sht_orthonormal, nthreads=0):
        """__init__(shtns_info self, int lmax, int mmax=-1, int mres=1, int norm=sht_orthonormal, int nthreads=0) -> sht"""
        this = _shtns.new_sht(lmax, mmax, mres, norm, nthreads)
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this

        		## array giving the degree of spherical harmonic coefficients.
        self.l = np.zeros(self.nlm, dtype=np.int32)
        ## array giving the order of spherical harmonic coefficients.
        self.m = np.zeros(self.nlm, dtype=np.int32)
        for mloop in range(0, self.mmax*self.mres+1, self.mres):
        	for lloop in range(mloop, self.lmax+1):
        		ii = self.idx(lloop,mloop)
        		self.m[ii] = mloop
        		self.l[ii] = lloop
        self.m.flags.writeable = False		# prevent writing in m and l arrays
        self.l.flags.writeable = False



    __swig_destroy__ = _shtns.delete_sht
    __del__ = lambda self: None

    def set_grid(self, nlat=0, nphi=0, flags=sht_quick_init, polar_opt=1.0e-8, nl_order=1):
        """set_grid(sht self, int nlat=0, int nphi=0, int flags=sht_quick_init, double polar_opt=1.0e-8, int nl_order=1)"""
        val = _shtns.sht_set_grid(self, nlat, nphi, flags, polar_opt, nl_order)

        		## array giving the cosine of the colatitude for the grid.
        self.cos_theta = self.__ct()
        self.cos_theta.flags.writeable = False
        ## shape of a spatial array for the grid (tuple of 2 values).
        self.spat_shape = tuple(self.__spat_shape())
        if self.nphi == 1:		# override spatial shape when nphi==1
        	self.spat_shape = (self.nlat, 1)
        	if flags & SHT_THETA_CONTIGUOUS: self.spat_shape = (1, self.nlat)


        return val


    def print_info(self):
        """print_info(sht self)"""
        return _shtns.sht_print_info(self)


    def sh00_1(self):
        """sh00_1(sht self) -> double"""
        return _shtns.sht_sh00_1(self)


    def sh10_ct(self):
        """sh10_ct(sht self) -> double"""
        return _shtns.sht_sh10_ct(self)


    def sh11_st(self):
        """sh11_st(sht self) -> double"""
        return _shtns.sht_sh11_st(self)


    def shlm_e1(self, l, m):
        """shlm_e1(sht self, unsigned int l, unsigned int m) -> double"""
        return _shtns.sht_shlm_e1(self, l, m)


    def __ct(self):
        """__ct(sht self) -> PyObject *"""
        return _shtns.sht___ct(self)


    def gauss_wts(self):
        """gauss_wts(sht self) -> PyObject *"""
        return _shtns.sht_gauss_wts(self)


    def mul_ct_matrix(self):
        """mul_ct_matrix(sht self) -> PyObject *"""
        return _shtns.sht_mul_ct_matrix(self)


    def st_dt_matrix(self):
        """st_dt_matrix(sht self) -> PyObject *"""
        return _shtns.sht_st_dt_matrix(self)


    def __spat_shape(self):
        """__spat_shape(sht self)"""
        return _shtns.sht___spat_shape(self)


    def spec_array(self, im=-1):
    	"""return a numpy array of spherical harmonic coefficients (complex). Adress coefficients with index sh.idx(l,m)
    	   if optional argument im is given, the spectral array is restricted to order im*mres."""
    	if im<0:
    		return np.zeros(self.nlm, dtype=complex)
    	else:
    		return np.zeros(self.lmax + 1 - im*self.mres, dtype=complex)

    def spat_array(self):
    	"""return a numpy array of 2D spatial field."""
    	if self.nlat == 0: raise RuntimeError("Grid not set. Call .set_grid() mehtod.")
    	return np.zeros(self.spat_shape)


    def idx(self, l, m):
        """idx(sht self, unsigned int l, unsigned int m) -> int"""
        return _shtns.sht_idx(self, l, m)


    def spat_to_SH(self, Vr, Qlm):
        """spat_to_SH(sht self, PyObject * Vr, PyObject * Qlm)"""
        return _shtns.sht_spat_to_SH(self, Vr, Qlm)


    def SH_to_spat(self, Qlm, Vr):
        """SH_to_spat(sht self, PyObject * Qlm, PyObject * Vr)"""
        return _shtns.sht_SH_to_spat(self, Qlm, Vr)


    def spat_cplx_to_SH(self, z, alm):
        """spat_cplx_to_SH(sht self, PyObject * z, PyObject * alm)"""
        return _shtns.sht_spat_cplx_to_SH(self, z, alm)


    def SH_to_spat_cplx(self, alm, z):
        """SH_to_spat_cplx(sht self, PyObject * alm, PyObject * z)"""
        return _shtns.sht_SH_to_spat_cplx(self, alm, z)


    def spat_to_SHsphtor(self, Vt, Vp, Slm, Tlm):
        """spat_to_SHsphtor(sht self, PyObject * Vt, PyObject * Vp, PyObject * Slm, PyObject * Tlm)"""
        return _shtns.sht_spat_to_SHsphtor(self, Vt, Vp, Slm, Tlm)


    def SHsphtor_to_spat(self, Slm, Tlm, Vt, Vp):
        """SHsphtor_to_spat(sht self, PyObject * Slm, PyObject * Tlm, PyObject * Vt, PyObject * Vp)"""
        return _shtns.sht_SHsphtor_to_spat(self, Slm, Tlm, Vt, Vp)


    def SHsph_to_spat(self, Slm, Vt, Vp):
        """SHsph_to_spat(sht self, PyObject * Slm, PyObject * Vt, PyObject * Vp)"""
        return _shtns.sht_SHsph_to_spat(self, Slm, Vt, Vp)


    def SHtor_to_spat(self, Tlm, Vt, Vp):
        """SHtor_to_spat(sht self, PyObject * Tlm, PyObject * Vt, PyObject * Vp)"""
        return _shtns.sht_SHtor_to_spat(self, Tlm, Vt, Vp)


    def spat_to_SHqst(self, Vr, Vt, Vp, Qlm, Slm, Tlm):
        """spat_to_SHqst(sht self, PyObject * Vr, PyObject * Vt, PyObject * Vp, PyObject * Qlm, PyObject * Slm, PyObject * Tlm)"""
        return _shtns.sht_spat_to_SHqst(self, Vr, Vt, Vp, Qlm, Slm, Tlm)


    def SHqst_to_spat(self, Qlm, Slm, Tlm, Vr, Vt, Vp):
        """SHqst_to_spat(sht self, PyObject * Qlm, PyObject * Slm, PyObject * Tlm, PyObject * Vr, PyObject * Vt, PyObject * Vp)"""
        return _shtns.sht_SHqst_to_spat(self, Qlm, Slm, Tlm, Vr, Vt, Vp)


    def synth(self,*arg):
    	"""
    	spectral to spatial transform, for scalar or vector data.
    	v = synth(qlm) : compute the spatial representation of the scalar qlm
    	vtheta,vphi = synth(slm,tlm) : compute the 2D spatial vector from its spectral spheroidal/toroidal scalars (slm,tlm)
    	vr,vtheta,vphi = synth(qlm,slm,tlm) : compute the 3D spatial vector from its spectral radial/spheroidal/toroidal scalars (qlm,slm,tlm)
    	"""
    	if self.nlat == 0: raise RuntimeError("Grid not set. Call .set_grid() mehtod.")
    	n = len(arg)
    	if (n>3) or (n<1): raise RuntimeError("1,2 or 3 arguments required.")
    	q = list(arg)
    	for i in range(0,n):
    		if q[i].size != self.nlm: raise RuntimeError("spectral array has wrong size.")
    		if q[i].dtype.num != np.dtype('complex128').num: raise RuntimeError("spectral array should be dtype=complex.")
    		if q[i].flags.contiguous == False: q[i] = q[i].copy()		# contiguous array required.
    	if n==1:	#scalar transform
    		vr = np.empty(self.spat_shape)
    		self.SH_to_spat(q[0],vr)
    		return vr
    	elif n==2:	# 2D vector transform
    		vt = np.empty(self.spat_shape)		# v_theta
    		vp = np.empty(self.spat_shape)		# v_phi
    		self.SHsphtor_to_spat(q[0],q[1],vt,vp)
    		return vt,vp
    	else:		# 3D vector transform
    		vr = np.empty(self.spat_shape)		# v_r
    		vt = np.empty(self.spat_shape)		# v_theta
    		vp = np.empty(self.spat_shape)		# v_phi
    		self.SHqst_to_spat(q[0],q[1],q[2],vr,vt,vp)
    		return vr,vt,vp

    def analys(self,*arg):
    	"""
    	spatial to spectral transform, for scalar or vector data.
    	qlm = analys(q) : compute the spherical harmonic representation of the scalar q
    	slm,tlm = analys(vtheta,vphi) : compute the spectral spheroidal/toroidal scalars (slm,tlm) from 2D vector components (vtheta, vphi)
    	qlm,slm,tlm = synth(vr,vtheta,vphi) : compute the spectral radial/spheroidal/toroidal scalars (qlm,slm,tlm) from 3D vector components (vr,vtheta,vphi)
    	"""
    	if self.nlat == 0: raise RuntimeError("Grid not set. Call .set_grid() mehtod.")
    	if abs(self.cos_theta[0]) == 1: raise RuntimeError("Analysis not allowed with sht_reg_poles grid.")
    	n = len(arg)
    	if (n>3) or (n<1): raise RuntimeError("1,2 or 3 arguments required.")
    	v = list(arg)
    	for i in range(0,n):
    		if v[i].shape != self.spat_shape: raise RuntimeError("spatial array has wrong shape.")
    		if v[i].dtype.num != np.dtype('float64').num: raise RuntimeError("spatial array should be dtype=float64.")
    		if v[i].flags.contiguous == False: v[i] = v[i].copy()		# contiguous array required.
    	if n==1:
    		q = np.empty(self.nlm, dtype=complex)
    		self.spat_to_SH(v[0],q)
    		return q
    	elif n==2:
    		s = np.empty(self.nlm, dtype=complex)
    		t = np.empty(self.nlm, dtype=complex)
    		self.spat_to_SHsphtor(v[0],v[1],s,t)
    		return s,t
    	else:
    		q = np.empty(self.nlm, dtype=complex)
    		s = np.empty(self.nlm, dtype=complex)
    		t = np.empty(self.nlm, dtype=complex)
    		self.spat_to_SHqst(v[0],v[1],v[2],q,s,t)
    		return q,s,t

    def synth_grad(self,slm):
    	"""(vtheta,vphi) = synth_grad(sht self, slm) : compute the spatial representation of the gradient of slm"""
    	if self.nlat == 0: raise RuntimeError("Grid not set. Call .set_grid() mehtod.")
    	if slm.size != self.nlm: raise RuntimeError("spectral array has wrong size.")
    	if slm.dtype.num != np.dtype('complex128').num: raise RuntimeError("spectral array should be dtype=complex.")
    	if slm.flags.contiguous == False: slm = slm.copy()		# contiguous array required.
    	vt = np.empty(self.spat_shape)
    	vp = np.empty(self.spat_shape)
    	self.SHsph_to_spat(slm,vt,vp)
    	return vt,vp

    def synth_cplx(self,alm):
    	"""
    	spectral to spatial transform, for complex valued scalar data.
    	z = synth(alm) : compute the spatial representation of the scalar alm
    	"""
    	if self.nlat == 0: raise RuntimeError("Grid not set. Call .set_grid() mehtod.")
    	if self.lmax != self.mmax: raise RuntimeError("complex SH requires lmax=mmax and mres=1.")
    	if alm.size != (self.lmax+1)**2: raise RuntimeError("spectral array has wrong size.")
    	if alm.dtype.num != np.dtype('complex128').num: raise RuntimeError("spectral array should be dtype=complex.")
    	if alm.flags.contiguous == False: alm = alm.copy()		# contiguous array required.
    	z = np.empty(self.spat_shape, dtype=complex)
    	self.SH_to_spat_cplx(alm,z)
    	return z

    def analys_cplx(self,z):
    	"""
    	spatial to spectral transform, for complex valued scalar data.
    	alm = analys(z) : compute the spherical harmonic representation of the complex scalar z
    	"""
    	if self.nlat == 0: raise RuntimeError("Grid not set. Call .set_grid() mehtod.")
    	if self.lmax != self.mmax: raise RuntimeError("complex SH requires lmax=mmax and mres=1.")
    	if z.shape != self.spat_shape: raise RuntimeError("spatial array has wrong shape.")
    	if z.dtype.num != np.dtype('complex128').num: raise RuntimeError("spatial array should be dtype=complex128.")
    	if z.flags.contiguous == False: z = z.copy()		# contiguous array required.
    	alm = np.empty((self.lmax+1)**2, dtype=complex)
    	self.spat_cplx_to_SH(z,alm)
    	return alm

    def zidx(self, l,m):
    	"""
    	zidx(sht self, int l, int m) -> int : compute the index l*(l+1)+m in a complex spherical harmonic expansion
    	"""
    	l = np.asarray(l)
    	m = np.asarray(m)
    	if (l>self.lmax).any() or (abs(m)>l).any() : raise RuntimeError("invalid range for l,m")
    	return l*(l+1)+m

    def zlm(self, idx):
    	"""
    	zlm(sht self, int idx) -> (int,int) : returns the l and m corresponding to the given index in complex spherical harmonic expansion
    	"""
    	idx = np.asarray(idx)
    	if (idx >= (self.lmax+1)**2).any() or (idx < 0).any() : raise RuntimeError("invalid range for l,m")
    	l = np.sqrt(idx).astype(int)
    	m = idx - l*(l+1)
    	return l,m

    def spec_array_cplx(self):
    	"""return a numpy array that can hold the spectral representation of a complex scalar spatial field."""
    	return np.zeros((self.lmax+1)**2, dtype=complex)

    def spat_array_cplx(self):
    	"""return a numpy array of 2D complex spatial field."""
    	if self.nlat == 0: raise RuntimeError("Grid not set. Call .set_grid() mehtod.")
    	return np.zeros(self.spat_shape, dtype=complex128)


    def SH_to_point(self, Qlm, cost, phi):
        """SH_to_point(sht self, PyObject * Qlm, double cost, double phi) -> double"""
        return _shtns.sht_SH_to_point(self, Qlm, cost, phi)


    def SH_to_grad_point(self, DrSlm, Slm, cost, phi):
        """SH_to_grad_point(sht self, PyObject * DrSlm, PyObject * Slm, double cost, double phi)"""
        return _shtns.sht_SH_to_grad_point(self, DrSlm, Slm, cost, phi)


    def SHqst_to_point(self, Qlm, Slm, Tlm, cost, phi):
        """SHqst_to_point(sht self, PyObject * Qlm, PyObject * Slm, PyObject * Tlm, double cost, double phi)"""
        return _shtns.sht_SHqst_to_point(self, Qlm, Slm, Tlm, cost, phi)


    def SH_to_lat(self, Qlm, cost, Vr):
        """SH_to_lat(sht self, PyObject * Qlm, double cost, PyObject * Vr)"""
        return _shtns.sht_SH_to_lat(self, Qlm, cost, Vr)


    def SHqst_to_lat(self, Qlm, Slm, Tlm, cost, Vr, Vt, Vp):
        """SHqst_to_lat(sht self, PyObject * Qlm, PyObject * Slm, PyObject * Tlm, double cost, PyObject * Vr, PyObject * Vt, PyObject * Vp)"""
        return _shtns.sht_SHqst_to_lat(self, Qlm, Slm, Tlm, cost, Vr, Vt, Vp)


    def Zrotate(self, Qlm, alpha):
        """Zrotate(sht self, PyObject * Qlm, double alpha) -> PyObject *"""
        return _shtns.sht_Zrotate(self, Qlm, alpha)


    def Yrotate(self, Qlm, alpha):
        """Yrotate(sht self, PyObject * Qlm, double alpha) -> PyObject *"""
        return _shtns.sht_Yrotate(self, Qlm, alpha)


    def Yrotate90(self, Qlm):
        """Yrotate90(sht self, PyObject * Qlm) -> PyObject *"""
        return _shtns.sht_Yrotate90(self, Qlm)


    def Xrotate90(self, Qlm):
        """Xrotate90(sht self, PyObject * Qlm) -> PyObject *"""
        return _shtns.sht_Xrotate90(self, Qlm)


    def SH_mul_mx(self, mx, Qlm):
        """SH_mul_mx(sht self, PyObject * mx, PyObject * Qlm) -> PyObject *"""
        return _shtns.sht_SH_mul_mx(self, mx, Qlm)


    def spat_to_SH_m(self, Vr, Qlm, im):
        """spat_to_SH_m(sht self, PyObject * Vr, PyObject * Qlm, PyObject * im)"""
        return _shtns.sht_spat_to_SH_m(self, Vr, Qlm, im)


    def SH_to_spat_m(self, Qlm, Vr, im):
        """SH_to_spat_m(sht self, PyObject * Qlm, PyObject * Vr, PyObject * im)"""
        return _shtns.sht_SH_to_spat_m(self, Qlm, Vr, im)


    def spat_to_SHsphtor_m(self, Vt, Vp, Slm, Tlm, im):
        """spat_to_SHsphtor_m(sht self, PyObject * Vt, PyObject * Vp, PyObject * Slm, PyObject * Tlm, PyObject * im)"""
        return _shtns.sht_spat_to_SHsphtor_m(self, Vt, Vp, Slm, Tlm, im)


    def SHsphtor_to_spat_m(self, Slm, Tlm, Vt, Vp, im):
        """SHsphtor_to_spat_m(sht self, PyObject * Slm, PyObject * Tlm, PyObject * Vt, PyObject * Vp, PyObject * im)"""
        return _shtns.sht_SHsphtor_to_spat_m(self, Slm, Tlm, Vt, Vp, im)


    def SHsph_to_spat_m(self, Slm, Vt, Vp, im):
        """SHsph_to_spat_m(sht self, PyObject * Slm, PyObject * Vt, PyObject * Vp, PyObject * im)"""
        return _shtns.sht_SHsph_to_spat_m(self, Slm, Vt, Vp, im)


    def SHtor_to_spat_m(self, Tlm, Vt, Vp, im):
        """SHtor_to_spat_m(sht self, PyObject * Tlm, PyObject * Vt, PyObject * Vp, PyObject * im)"""
        return _shtns.sht_SHtor_to_spat_m(self, Tlm, Vt, Vp, im)


    def spat_to_SHqst_m(self, Vr, Vt, Vp, Qlm, Slm, Tlm, im):
        """spat_to_SHqst_m(sht self, PyObject * Vr, PyObject * Vt, PyObject * Vp, PyObject * Qlm, PyObject * Slm, PyObject * Tlm, PyObject * im)"""
        return _shtns.sht_spat_to_SHqst_m(self, Vr, Vt, Vp, Qlm, Slm, Tlm, im)


    def SHqst_to_spat_m(self, Qlm, Slm, Tlm, Vr, Vt, Vp, im):
        """SHqst_to_spat_m(sht self, PyObject * Qlm, PyObject * Slm, PyObject * Tlm, PyObject * Vr, PyObject * Vt, PyObject * Vp, PyObject * im)"""
        return _shtns.sht_SHqst_to_spat_m(self, Qlm, Slm, Tlm, Vr, Vt, Vp, im)

sht_swigregister = _shtns.sht_swigregister
sht_swigregister(sht)


def nlm_calc(lmax, mmax, mres):
    """nlm_calc(long lmax, long mmax, long mres) -> long"""
    return _shtns.nlm_calc(lmax, mmax, mres)

def set_verbosity(arg1):
    """set_verbosity(int arg1)"""
    return _shtns.set_verbosity(arg1)

def print_version():
    """print_version()"""
    return _shtns.print_version()
# This file is compatible with both classic and new-style classes.


