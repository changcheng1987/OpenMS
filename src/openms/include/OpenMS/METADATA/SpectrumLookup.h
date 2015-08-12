// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2015.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Hendrik Weisser $
// $Authors: Hendrik Weisser $
// --------------------------------------------------------------------------

#ifndef OPENMS_METADATA_SPECTRUMLOOKUP_H
#define OPENMS_METADATA_SPECTRUMLOOKUP_H

#include <OpenMS/KERNEL/MSSpectrum.h>

#include <boost/regex.hpp>

namespace OpenMS
{
  /**
    @brief Helper class for looking up spectra based on RT, index or native ID
  */
  class OPENMS_DLLAPI SpectrumLookup
  {
  public:

    /// Bit mask for which meta data to extract from a spectrum
    typedef unsigned char MetaDataFlags;

    /// Possible meta data to extract from a spectrum
    static const MetaDataFlags METADATA_RT = 1, METADATA_MZ = 2,
      METADATA_CHARGE = 4, METADATA_NATIVEID = 8, METADATA_ALL = 15;

    /// Meta data of a spectrum
    struct SpectrumMetaData
    {
      double rt;
      double mz;
      Int charge;
      String native_ID;

      SpectrumMetaData(): rt(0.0), mz(0.0), charge(0), native_ID("")
      {
      }
    };

    /// Format of a spectrum reference
    struct ReferenceFormat
    {
      boost::regex re;
      bool count_from_one;
      double rt_tolerance;
    };

    /// Constructor
    SpectrumLookup(std::vector<MSSpectrum<> >& spectra,
                   const String& id_regexp_match = "",
                   const String& id_regexp_replace = "");

    /// Destructor
    virtual ~SpectrumLookup();

    /// Look up spectrum by retention time (RT)
    MSSpectrum<>& findByRT(double rt, double tolerance = 0.01) const;

    /// Look up spectrum by native ID
    MSSpectrum<>& findByNativeID(const String& native_id) const;
    
    /// Look up spectrum by index
    MSSpectrum<>& findByIndex(Size index, bool count_from_one = false) const;

    /// Extract meta data from a spectrum
    static void getSpectrumMetaData(const MSSpectrum<>& spectrum,
                                    SpectrumMetaData& metadata,
                                    MetaDataFlags flags = METADATA_ALL);

    /// Register a possible format for a spectrum reference
    void addReferenceFormat(const String& regexp, bool count_from_one = false,
                            double rt_tolerance = 0.01);

    /// Look up spectrum by reference
    MSSpectrum<>& findByReference(const String& spectrum_ref) const;

    /// Extract meta data from a spectrum reference (only look up the spectrum if necessary)
    void getSpectrumMetaDataByReference(
      const String& spectrum_ref, SpectrumMetaData& metadata, 
      MetaDataFlags flags= METADATA_ALL) const;

  protected:

    std::vector<MSSpectrum<> >& spectra_; ///< Reference to spectra

    /// Possible formats of spectrum references
    std::vector<ReferenceFormat> reference_formats_;

    std::map<double, Size> rts_; ///< Mapping: RT -> spectrum index
    std::map<String, Size> ids_; ///< Mapping: native ID -> spectrum index

    /// Look up spectrum by regular expression match
    MSSpectrum<>& findByRegExpMatch_(
      const String& spectrum_ref, const String& regexp, 
      const boost::smatch& match, bool count_from_one, double rt_tolerance)
      const;
    
  private:
    /// Copy constructor (not implemented)
    SpectrumLookup(const SpectrumLookup&);

    /// Assignment operator (not implemented)
    SpectrumLookup& operator=(const SpectrumLookup&);

  };

} //namespace OpenMS

#endif // OPENMS_METADATA_SPECTRUMLOOKUP_H
