/**
 * (c) 2013 by Mega Limited, Auckland, New Zealand
 *
 * This file is part of MEGAcmd.
 *
 * MEGAcmd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * @copyright Simplified (2-clause) BSD License.
 *
 * You should have received a copy of the license along with this
 * program.
 */

#pragma once

#include <memory>

#include "megacmdcommonutils.h"
#include "sync_issues.h"

using namespace megacmd;

namespace SyncCommand
{
    std::unique_ptr<mega::MegaSync> getSync(mega::MegaApi& api, const std::string& pathOrId);
    std::unique_ptr<mega::MegaSync> reloadSync(mega::MegaApi& api, std::unique_ptr<mega::MegaSync>&& sync);

    bool isAnySyncUploadDelayed(mega::MegaApi& api);

    void printSync(mega::MegaApi& api, ColumnDisplayer& cd, bool showHandle, mega::MegaSync& sync,  const SyncIssueList& syncIssues);
    void printSyncList(mega::MegaApi& api, ColumnDisplayer& cd, bool showHandles, const mega::MegaSyncList& syncList, const SyncIssueList& syncIssues);

    void addSync(mega::MegaApi& api, const fs::path& localPath, mega::MegaNode& node);

    enum class ModifyOpts
    {
        Pause,
        Enable,
        Delete
    };

    void modifySync(mega::MegaApi& api, mega::MegaSync& sync, ModifyOpts opts);
}

namespace GlobalSyncConfig
{
    void loadFromConfigurationManager(mega::MegaApi& api);

    namespace DelayedUploads
    {
        struct Config
        {
            int mWaitSecs = 0;
            int mMaxAttempts = 0;
        };
        std::optional<Config> getCurrentConfig(mega::MegaApi& api);

        struct Limits
        {
            Config mLower;
            Config mUpper;

            bool isWaitSecsValid(int waitSecs) const;
            bool isMaxAttemptsValid(int maxAttempts) const;
        };
        std::optional<Limits> getCurrentLimits(mega::MegaApi& api);

        void updateWaitSecs(mega::MegaApi& api, int waitSecs);
        void updateMaxAttempts(mega::MegaApi& api, int waitSecs);
    }
}
