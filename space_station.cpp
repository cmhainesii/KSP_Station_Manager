#include "include/space_station.hpp"
#include "include/utils.hpp"
#include "include/devices.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <fmt/core.h>

using SpaceStation = KSP_SM::SpaceStationBuilder::SpaceStation;
using SpaceStationBuilder = KSP_SM::SpaceStationBuilder;
using std::endl;
using std::string;
using std::stringstream;



namespace KSP_SM
{

   

    SpaceStation::SpaceStation(string station_id) noexcept
    {
        this->m_station_id = station_id;
    }

    SpaceStationBuilder::SpaceStationBuilder(string station_id)
    {
        this->m_space_station = std::make_unique<KSP_SM::SpaceStationBuilder::SpaceStation>(station_id);
        //std::unique_ptr<SpaceStation>(new SpaceStation(station_id));
    }

  

    string SpaceStation::ToString()
    {
        stringstream ss;
        string tab = "\t";

        ss << "Station Information" << endl;
        ss << endl;
        ss << "Station ID: " << m_station_id << endl;
        ss << "Station Name: " << m_station_name << endl;
        ss << fmt::format("Orbiting Planet: {}", Utility::PlanetToString(m_orbiting_body)) << endl;
        ss << "Orbit Details: " << endl;
        ss << fmt::format("\t Apoapsis: {} meters\n", Utility::numberWithCommas(m_orbit_details.apoapsis));
        ss << fmt::format("\tPeriapsis: {} meters\n", Utility::numberWithCommas(m_orbit_details.periapsis));
        ss << fmt::format("Capacity: {} kerbals", m_capacity) << endl;
        ss << fmt::format("Station Currently Active: {}", Utility::BoolToYesNo(m_active)) << endl;

        ss << "Communication Equipment: \n";

        std::array<std::size_t, NUM_COMM_DEVICES> comm_counts = m_comms_dev_quantities.GetAsArray();
        for (auto i = 0; i < NUM_COMM_DEVICES; ++i)
        {
            if(comm_counts.at(i) > 0)
            {
                ss << fmt::format("\t{:25}: {:4}\n", CommsDeviceToString(static_cast<CommunicationDevice>(i)), comm_counts.at(i));
            }
        }

        ss << "\n";


        ss << "Docking Ports Installed: \n";
        std::array<std::size_t, NUM_DOCKING_PORTS> docking_counts = m_port_quantities.GetAsArray();
        for(auto i = 0; i < NUM_DOCKING_PORTS; ++i)
        {
            if(docking_counts.at(i) > 0)
            {
                ss << fmt::format("\t{:25}: {:4}\n", DockingPortToString(static_cast<DockingPort>(i)) , docking_counts.at(i));    
            }
        }
        
        ss << "\n";

        ss << "Kerbals Present: " << endl;
        if (m_kerbals.size() > 0)
        {
            
            for (auto current : m_kerbals)
            {
                ss << fmt::format("{}{}", tab, current) << endl;
            }
        }
        else
        {
            ss << tab << "No kerbals currently onboard.\n";
        }

        return ss.str();
    }

    SpaceStationBuilder &SpaceStationBuilder::SetName(const string &name)
    {
        m_space_station->m_station_name = name;
        return *this;
    }

    SpaceStationBuilder &SpaceStationBuilder::SetOrbitDetails(OrbitalParameters params)
    {
        m_space_station->m_orbit_details = params;
        return *this;
    }

    SpaceStationBuilder &SpaceStationBuilder::SetOrbitDetails(size_t apoapsis, size_t periapsis)
    {
        OrbitalParameters params;
        params.apoapsis = apoapsis;
        params.periapsis = periapsis;

        m_space_station->m_orbit_details = params;
        return *this;
    }

    SpaceStationBuilder &SpaceStationBuilder::SetCapacity(size_t capacity)
    {
        m_space_station->m_capacity = capacity;
        return *this;
    }

    SpaceStationBuilder &SpaceStationBuilder::SetActive(bool active)
    {
        m_space_station->m_active = active;
        return *this;
    }

    SpaceStationBuilder &SpaceStationBuilder::AddKerbal(string name)
    {
        if (!name.empty())
        {
            m_space_station->m_kerbals.push_back(name);
        }

        return *this;
    }

    SpaceStationBuilder &SpaceStationBuilder::SetOrbitingBody(CelestialBody planet)
    {
        m_space_station->m_orbiting_body = planet;
        return *this;
    }

    SpaceStationBuilder& SpaceStationBuilder::SetDockingPortQuantities(const DockingPortCount& quantities)
    {
        this->m_space_station->m_port_quantities = quantities;
        return *this;
    }

    SpaceStationBuilder& SpaceStationBuilder::SetCommsDevicesQuantities(const CommsDevCount& quantities)
    {
        this->m_space_station->m_comms_dev_quantities = quantities;
        return *this;
    }

    std::unique_ptr<SpaceStation> SpaceStationBuilder::build()
    {
        return std::move(m_space_station);
    }

    string SpaceStation::CommsDeviceToString(CommunicationDevice dev)
    {
        switch (dev)
        {

        default:
        case CommunicationDevice::COMM_16:
            return "Communotron 16";
        case CommunicationDevice::COMM_16S:
            return "Communotron 16-S";
        case CommunicationDevice::RA_15:
            return "RA-15";
        case CommunicationDevice::RA_2:
            return "RA-2";
        case CommunicationDevice::COMM_88_88:
            return "Communotron 88-88";
        case CommunicationDevice::COMM_DTS_M1:
            return "Communotron DTS-M1";
        case CommunicationDevice::COMM_HG_5:
            return "Communotron HG-5";
        case CommunicationDevice::COMM_HG_55:
            return "Communotron HG-55";
        case CommunicationDevice::RA_100:
            return "RA-100";
        }
    }

    string SpaceStation::DockingPortToString(DockingPort port)
    {
        string dp = "Docking Port";
        string output;

        switch (port)
        {

        default:
        case DockingPort::XSMALL:
            output = "Extra Small ";
            break;
        case DockingPort::SMALL:
            output = "Small ";
            break;
        case DockingPort::MEDIUM:
            output = "Medium ";
            break;
        case DockingPort::LARGE:
            output = "Large ";
            break;
        case DockingPort::XLARGE:
            output = "Extra Large ";
        }

        return output + dp;
    }

    string SpaceStation::GetName() const
    {
        return m_station_name;
    }

    string SpaceStation::GetStationID() const
    {
        return m_station_id;
    }

    size_t SpaceStation::GetCapacity() const
    {
        return m_capacity;
    }

    bool SpaceStation::isActive() const
    {
        return m_active;
    }

    OrbitalParameters SpaceStation::GetOrbitalDetails() const
    {
        return m_orbit_details;
    }

    void to_json(json& j, const SpaceStation& ss)
    {
        j = json{{"id", ss.m_station_id}, {"name", ss.m_station_name},
                {"active", ss.m_active},
                {"capacity", ss.m_capacity},
                {"kerbals", ss.m_kerbals}, {"apoapsis", ss.m_orbit_details.apoapsis},
                {"periapsis", ss.m_orbit_details.periapsis}, {"orbiting", ss.m_orbiting_body},
                {"port_quan_xs", ss.m_port_quantities.xs}, {"port_quan_sm", ss.m_port_quantities.sm},
                {"port_quan_md", ss.m_port_quantities.md}, {"port_quan_lg", ss.m_port_quantities.lg},
                {"port_quan_xl", ss.m_port_quantities.xl},
                {"comms_0", ss.m_comms_dev_quantities.C16}, {"comms_1", ss.m_comms_dev_quantities.C16S},
                {"comms_2", ss.m_comms_dev_quantities.C8888}, {"comms_3", ss.m_comms_dev_quantities.CDTS},
                {"comms_4", ss.m_comms_dev_quantities.CHG55}, {"comms_5", ss.m_comms_dev_quantities.CHG5},
                {"comms_6", ss.m_comms_dev_quantities.RA100}, {"comms_7", ss.m_comms_dev_quantities.RA15},
                {"comms_8", ss.m_comms_dev_quantities.RA2}
                };

    
    }

    void to_json(json& j, const std::unique_ptr<SpaceStation>& ss)
    {
        j = json{{"id", ss->m_station_id}, {"name", ss->m_station_name},
                {"active", ss->m_active},
                {"capacity", ss->m_capacity},
                {"kerbals", ss->m_kerbals}, {"apoapsis", ss->m_orbit_details.apoapsis},
                {"periapsis", ss->m_orbit_details.periapsis}, {"orbiting", ss->m_orbiting_body},
                {"port_quan_xs", ss->m_port_quantities.xs}, {"port_quan_sm", ss->m_port_quantities.sm},
                {"port_quan_md", ss->m_port_quantities.md}, {"port_quan_lg", ss->m_port_quantities.lg},
                {"port_quan_xl", ss->m_port_quantities.xl}, {"comms_0", ss->m_comms_dev_quantities.C16},
                {"comms_1", ss->m_comms_dev_quantities.C16S}, {"comms_2", ss->m_comms_dev_quantities.C8888},
                {"comms_3", ss->m_comms_dev_quantities.CDTS}, {"comms_4", ss->m_comms_dev_quantities.CHG55},
                {"comms_5", ss->m_comms_dev_quantities.CHG5}, {"comms_6", ss->m_comms_dev_quantities.RA100},
                {"comms_7", ss->m_comms_dev_quantities.RA15}, {"comms_8", ss->m_comms_dev_quantities.RA2}
                };

    }

    void from_json(const json& j, std::unique_ptr<SpaceStation>& ss)
    {
        ss.reset(new SpaceStation());
        j.at("id").get_to(ss->m_station_id);
        j.at("name").get_to(ss->m_station_name);
        j.at("active").get_to(ss->m_active);
        j.at("capacity").get_to(ss->m_capacity);
        j.at("apoapsis").get_to(ss->m_orbit_details.apoapsis);
        j.at("periapsis").get_to(ss->m_orbit_details.periapsis);
        j.at("orbiting").get_to(ss->m_orbiting_body);
        j.at("kerbals").get_to(ss->m_kerbals);
        j.at("port_quan_xs").get_to(ss->m_port_quantities.xs);
        j.at("port_quan_sm").get_to(ss->m_port_quantities.sm);
        j.at("port_quan_md").get_to(ss->m_port_quantities.md);
        j.at("port_quan_lg").get_to(ss->m_port_quantities.lg);
        j.at("port_quan_xl").get_to(ss->m_port_quantities.xl);
        j.at("comms_0").get_to(ss->m_comms_dev_quantities.C16);
        j.at("comms_1").get_to(ss->m_comms_dev_quantities.C16S);
        j.at("comms_2").get_to(ss->m_comms_dev_quantities.C8888);
        j.at("comms_3").get_to(ss->m_comms_dev_quantities.CDTS);
        j.at("comms_4").get_to(ss->m_comms_dev_quantities.CHG55);
        j.at("comms_5").get_to(ss->m_comms_dev_quantities.CHG5);
        j.at("comms_6").get_to(ss->m_comms_dev_quantities.RA100);
        j.at("comms_7").get_to(ss->m_comms_dev_quantities.RA15);
        j.at("comms_8").get_to(ss->m_comms_dev_quantities.RA2);
    }

    

    void from_json(const json& j, SpaceStation& ss)
    {
        j.at("id").get_to(ss.m_station_id);
        j.at("name").get_to(ss.m_station_name);
        j.at("active").get_to(ss.m_active);
        j.at("capacity").get_to(ss.m_capacity);
        j.at("apoapsis").get_to(ss.m_orbit_details.apoapsis);
        j.at("periapsis").get_to(ss.m_orbit_details.periapsis);
        j.at("orbiting").get_to(ss.m_orbiting_body);
        j.at("kerbals").get_to(ss.m_kerbals);
        j.at("port_quan_xs").get_to(ss.m_port_quantities.xs);
        j.at("port_quan_sm").get_to(ss.m_port_quantities.sm);
        j.at("port_quan_md").get_to(ss.m_port_quantities.md);
        j.at("port_quan_lg").get_to(ss.m_port_quantities.lg);
        j.at("port_quan_xl").get_to(ss.m_port_quantities.xl);
        j.at("comms_0").get_to(ss.m_comms_dev_quantities.C16);
        j.at("comms_1").get_to(ss.m_comms_dev_quantities.C16S);
        j.at("comms_2").get_to(ss.m_comms_dev_quantities.C8888);
        j.at("comms_3").get_to(ss.m_comms_dev_quantities.CDTS);
        j.at("comms_4").get_to(ss.m_comms_dev_quantities.CHG55);
        j.at("comms_5").get_to(ss.m_comms_dev_quantities.CHG5);
        j.at("comms_6").get_to(ss.m_comms_dev_quantities.RA100);
        j.at("comms_7").get_to(ss.m_comms_dev_quantities.RA15);
        j.at("comms_8").get_to(ss.m_comms_dev_quantities.RA2);
    }

    OrbitalParameters::OrbitalParameters(size_t ap, size_t pe)
    {
        apoapsis = ap;
        periapsis = pe;
    }

    SpaceStation::~SpaceStation()
    {
        std::cout << "I'm being deleted!" << std::endl;
    }

    SpaceStationBuilder& SpaceStationBuilder::AddKerbals(const vector<string>& kerbals)
    {
        m_space_station->m_kerbals = kerbals;
        return *this;
    }

    std::unique_ptr<SpaceStation> SpaceStationBuilder::createStationFromConsoleInput()
    {
        bool validInput = false;
        bool doneEnteringList = false;
        string buffer;
        string station_id;
        string station_name;
        DockingPortCount port_quantities;
        CommsDevCount comms_dev_quantities;
        std::array<std::size_t, 5> port_builder {};
        std::array<std::size_t, 9> comms_builder {};
        vector<string> kerbals;
        size_t capacity;
        bool active;
        OrbitalParameters params;
        CelestialBody orbiting;
        
        

        // Call ignore on any extra input from the menu selection
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while(!validInput)
        {
            std::cout << "Enter Station ID: ";
            std::getline(std::cin, buffer); 

            if(buffer.compare("") != 0)
            {
                station_id = buffer;
                validInput = true;
                continue;
            }
            std::cout << "Invalid response" << std::endl;
        }

        validInput = false;

        while(!validInput)
        {
            std::cout << "Enter Station Name: ";
            std::getline(std::cin, buffer);

            if (buffer.compare("") != 0)
            {
                validInput = true;
                station_name = buffer;
                continue;
            }
            std::cerr << "Invalid Response" << std::endl;
        }

        validInput = false;

        std::cout << "Enter Station Kerbal Capacity: ";
        while(!(std::cin >> capacity))
        {
            std::cout << "Invalid Response. Must be an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter Station Kerbal Capacity: ";
        }

        // Clear input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while(!validInput)
        {
            std::cout << "Is station currently active? (y or n): ";
            std::cin >> buffer;

            char firstChar = buffer.at(0);
            firstChar = tolower(firstChar);

            if(firstChar == 'y')
            {
                active = true;
                validInput = true;
                continue;
            }
            if(firstChar == 'n')
            {
                active = false;
                validInput = true;
                continue;
            }

            std::cout << "Invalid Response" << std::endl;
        }

        validInput = false;

        // Clear input buffer!
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while(!validInput)
        {
            std::cout << "Station is Orbiting: ";
            std::getline(std::cin, buffer);

            for(std::size_t i = 0; i < buffer.length(); ++i)
            {
                buffer.at(i) = std::tolower(buffer.at(i));
            }
            
            if(buffer.compare("kerbol") == 0)
            {
                orbiting = CelestialBody::KERBOL;
                validInput = true;
                continue;
            }
            if(buffer.compare("moho") == 0)
            {
                orbiting = CelestialBody::MOHO;
                validInput = true;
                continue;
            }
            if(buffer.compare("eve") == 0)
            {
                orbiting = CelestialBody::EVE;
                validInput = true;
                continue;
            }
            if(buffer.compare("gilly") == 0)
            {
                orbiting = CelestialBody::GILLY;
                validInput = true;
                continue;
            }
            if(buffer.compare("kerbin") == 0)
            {
                orbiting = CelestialBody::KERBIN;
                validInput = true;
                continue;
            }
            if(buffer.compare("mun") == 0)
            {
                orbiting = CelestialBody::MUN;
                validInput = true;
                continue;
            }
            if(buffer.compare("minmus") == 0)
            {
                orbiting = CelestialBody::MINMUS;
                validInput = true;
                continue;
            }
            if(buffer.compare("duna") == 0)
            {
                orbiting = CelestialBody::DUNA;
                validInput = true;
                continue;
            }
            if(buffer.compare("ike") == 0)
            {
                orbiting = CelestialBody::IKE;
                validInput = true;
                continue;
            }
            if(buffer.compare("dres") == 0)
            {
                orbiting = CelestialBody::DRES;
                validInput = true;
                continue;
            }
            if(buffer.compare("jool") == 0)
            {
                orbiting = CelestialBody::JOOL;
                validInput = true;
                continue;
            }
            if(buffer.compare("laythe") == 0)
            {
                orbiting = CelestialBody::LAYTHE;
                validInput = true;
                continue;
            }
            if(buffer.compare("vall") == 0)
            {
                orbiting = CelestialBody::VALL;
                validInput = true;
                continue;
            }
            if(buffer.compare("tylo") == 0)
            {
                orbiting = CelestialBody::TYLO;
                validInput = true;
                continue;
            }
            if(buffer.compare("bop") == 0)
            {
                orbiting = CelestialBody::BOP;
                validInput = true;
                continue;
            }
            if(buffer.compare("pol") == 0)
            {
                orbiting = CelestialBody::POL;
                validInput = true;
                continue;
            }
            if(buffer.compare("eloo") == 0)
            {
                orbiting = CelestialBody::ELOO;
                validInput = true;
                continue;
            }

            std::cout << "Invalid Response. Must be a valid planet or moon." << std::endl;

        }



        validInput = false;
        while(!validInput)
        {
            bool thousand = false;
            std::cout << "Enter Station Apoapsis: ";
            std::getline(std::cin, buffer);

            if(buffer.size() > 0 && std::tolower(buffer.at(buffer.size() - 1)) == 'k')
            {
                thousand = true;
            }

            try {
                params.apoapsis = std::stoi(buffer);
                if(thousand)
                {
                    params.apoapsis *= 1000;
                }
                validInput = true;
            }
            catch (std::invalid_argument& e) {
                std::cout << "Invalid Response\n";
                continue;
            }

        }


        validInput = false;
        while(!validInput)
        {
            bool thousand = false;
            std::cout << "Enter Station Periapsis: ";
            std::getline(std::cin, buffer);

            if(buffer.size() > 0 && std::tolower(buffer.at(buffer.size() - 1)) == 'k')
            {
                thousand = true;
            }

            try {
                params.periapsis = std::stoi(buffer);
                if (thousand)
                {
                    params.periapsis *= 1000;
                }
                validInput = true;
            }
            catch (std::invalid_argument& e)
            {
                std::cout << "Invalid Response\n";
                continue;
            }
        }
        

        std::cout << "AP: " << Utility::numberWithCommas(params.apoapsis) << std::endl;
        std::cout << "PE: " << Utility::numberWithCommas(params.periapsis) << std::endl;

        validInput = false;

        // here

        validInput = false;
        char selection;
        DockingPort selectedDp;
        int quantity = 0;


        while(!doneEnteringList)
        {
            std::cout << "Enter Station Docking Ports" << std::endl << std::endl;
            std::cout << "a) XSmall" << std::endl;
            std::cout << "b) Small" << std::endl;
            std::cout << "c) Medium" << std::endl;
            std::cout << "d) Large" << std::endl;
            std::cout << "e) XLarge" << std::endl;
            std::cout << "f) done" << std::endl << std::endl;
            std::cout << "Enter Selection: ";
            while(!(std::cin >> selection))
            {
                std::cout << "Invalid Response" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Selection: ";
            }

            // check a valid selection was made
            switch(std::tolower(selection))
            {
                case 'a':
                    selectedDp = DockingPort::XSMALL;
                    break;
                case 'b':
                    selectedDp = DockingPort::SMALL;
                    break;
                case 'c':
                    selectedDp = DockingPort::MEDIUM;
                    break;
                case 'd':
                    selectedDp = DockingPort::LARGE;
                case 'e':
                    selectedDp = DockingPort::XLARGE;
                    break;
                case 'f':
                    doneEnteringList = true;
                    continue;
                default:
                    std::cout << "Invalid Response" << std::endl;
                    continue;

            }

            std::cout << "Enter quantity of selected docking port: ";
            while(!(std::cin >> quantity))
            {
                std::cout << "Invalid Response. Must be an integer." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter quantity of selected docking port: ";
            }

            port_builder.at(static_cast<int>(selectedDp)) = quantity;


            
        }

        

        port_quantities = DockingPortCount(port_builder);

        std::cout << "Quantities:\n";
        std::cout << fmt::format("XS: {}\n", port_quantities.xs);
        std::cout << fmt::format("SM: {}\n", port_quantities.sm);
        std::cout << fmt::format("MD: {}\n", port_quantities.md);
        std::cout << fmt::format("LG: {}\n", port_quantities.lg);
        std::cout << fmt::format("XL: {}\n", port_quantities.xl);


        doneEnteringList = false;
        CommunicationDevice selectedDevice;

        while(!doneEnteringList)
        {
            // COMM_16,
            // COMM_16S,
            // RA_15,
            // RA_2,
            // COMM_88_88,
            // COMM_DTS_M1,
            // COMM_HG_5,
            // COMM_HG_55,
            // RA_100,
            std::cout << "Enter Communication Devices" << std::endl << std::endl;
            std::cout << "a) Communotron 16" << std::endl;
            std::cout << "b) Communotron 16S" << std::endl;
            std::cout << "c) RA-15" << std::endl;
            std::cout << "d) RA-2" << std::endl;
            std::cout << "e) Communotron 88-88" << std::endl;
            std::cout << "f) Communotron DTS-M1" << std::endl;
            std::cout << "g) Communotron HG-5" << std::endl;
            std::cout << "h) Communotron HG-55" << std::endl;
            std::cout << "i) RA-100" << std::endl;
            std::cout << "j) done" << std::endl;
            std::cout << "Enter Selection: ";

            while(!(std::cin >> selection))
            {
                std::cout << "Invalid Response" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Selection: ";   
            }

            selection = std::tolower(selection);

            // Validate selection
            switch(selection)
            {
                case 'a':
                    selectedDevice = CommunicationDevice::COMM_16;
                    break;
                case 'b':
                    selectedDevice = CommunicationDevice::COMM_16S;
                    break;
                case 'c':
                    selectedDevice = CommunicationDevice::RA_15;
                    break;
                case 'd':
                    selectedDevice = CommunicationDevice::RA_2;
                    break;
                case 'e':
                    selectedDevice = CommunicationDevice::COMM_88_88;
                    break;
                case 'f':
                    selectedDevice = CommunicationDevice::COMM_DTS_M1;
                    break;
                case 'g':
                    selectedDevice = CommunicationDevice::COMM_HG_5;
                    break;
                case 'h':
                    selectedDevice = CommunicationDevice::COMM_HG_55;
                    break;
                case 'i':
                    selectedDevice = CommunicationDevice::RA_100;
                    break;
                case 'j':
                    doneEnteringList = true;
                    continue;
                default:
                    std::cout << "Invalid Response" << std::endl;
                    continue;
            }

            std::cout << "Enter Quanity of Selected Communication Device: ";
            while(!(std::cin >> quantity))
            {
                std::cerr << "Invalid Response. Must be an integer." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Quanity of Selected Communication Device: ";
            }

            comms_builder.at(static_cast<int>(selectedDevice)) = quantity;
        }

        comms_dev_quantities = CommsDevCount(comms_builder);

        doneEnteringList = false;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while(!doneEnteringList)
        {

            std::cout << "Enter Kerbals Currently On-Board. Leave blank when finished." << std::endl;
            std::cout << "Enter Kerbal Name: ";
            std::getline(std::cin, buffer);
            
            if(buffer.compare("") == 0)
            {
                doneEnteringList = true;
                continue;
            }

            // Add kerbal to list
            kerbals.push_back(buffer);

        }

        // Build new station!
        auto newStation = SpaceStationBuilder(station_id)
            .SetName(station_name)
            .SetCapacity(capacity)
            .SetActive(active)
            .SetOrbitDetails(params)
            .SetOrbitingBody(orbiting)
            .SetDockingPortQuantities(port_quantities)
            .SetCommsDevicesQuantities(comms_dev_quantities)
            .AddKerbals(kerbals)
            .build();
        

        return newStation;


    }
}


