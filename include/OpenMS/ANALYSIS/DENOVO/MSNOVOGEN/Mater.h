// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2013.
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
// $Maintainer: Jens Allmer $
// $Authors: Jens Allmer $
// --------------------------------------------------------------------------

#ifndef OPENMS_ANALYSIS_DENOVO_MSNOVOGEN_MATER_H
#define OPENMS_ANALYSIS_DENOVO_MSNOVOGEN_MATER_H

#include <OpenMS/config.h>
#include <OpenMS/CHEMISTRY/Residue.h>
#include <OpenMS/ANALYSIS/DENOVO/MSNOVOGEN/Chromosome.h>
#include <vector>

namespace OpenMS
{
  class OPENMS_DLLAPI Mater
  {
private:
	/// Seed to initialize rand
	unsigned int randomSeed_;
	/// A list of amino acids that can form a sequence is needed for some mutation processes.
	std::vector<const Residue*> aaList_;
	/// it is necessary to know the precursor mass to propose suitable sequences
	double precursorMass_;
	/// it is necessary to know the precursor mass to propose suitable sequences
	double precursorMassTolerance_;

private:
	/// Copy c'tor
	Mater(const Mater& other);

	/// Assignment operator
	Mater & operator=(const Mater& rhs);

public:
    /// Default c'tor
    Mater(double precursorMass, double precursorMassTolerance, std::vector<const Residue*> aaList);

    virtual std::vector<Chromosome> mate(const Chromosome& lhs, const Chromosome & rhs) = 0;

	/// to change the seed or to fix it for unit tests.
	void seed(const unsigned int seed);

	unsigned int getSeed() const
	{
		return randomSeed_;
	}

	const std::vector<const Residue*>& getAAList() const {
		return aaList_;
	}

	void setAAList(const std::vector<const Residue*>& aaList) {
		aaList_ = aaList;
	}

	double getPrecursorMass() const {
		return precursorMass_;
	}

	void setPrecursorMass(double precursorMass) {
		precursorMass_ = precursorMass;
	}

	double getPrecursorMassTolerance() const {
		return precursorMassTolerance_;
	}

	void setPrecursorMassTolerance(double precursorMassTolerance) {
		precursorMassTolerance_ = precursorMassTolerance;
	}

	unsigned int getRandomSeed() const {
		return randomSeed_;
	}

	void setRandomSeed(unsigned int randomSeed) {
		randomSeed_ = randomSeed;
	}
  };
} // namespace

#endif // OPENMS_ANALYSIS_DENOVO_MSNOVOGEN_MATER_H