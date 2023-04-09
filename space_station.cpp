#include "include/space_station.hpp"
#include "include/utils.hpp"
#include <sstream>
#include <iostream>
#include <fmt/core.h>

using SpaceStation = KSP_SM::SpaceStationBuilder::SpaceStation;
using SpaceStationBuilder = KSP_SM::SpaceStationBuilder;
using std::endl;
using std::string;
using std::stringstream;

namespace KSP_SM
{

    SpaceStation::SpaceStation(string station_id)
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
        ss << '\t' << " Apoapsis: " << m_orbit_details.apoapsis << endl;
        ss << '\t' << "Periapsis: " << m_orbit_details.periapsis << endl;
        ss << fmt::format("Capacity: {} kerbals", m_capacity) << endl;
        ss << fmt::format("Station Currently Active: {}", Utility::BoolToYesNo(m_active)) << endl;
        if (m_comms_devices.size() > 0)
        {
            ss << "Communication Equipment: " << endl;
            for (auto current : m_comms_devices)
            {
                ss << fmt::format("{}{}", tab, SpaceStation::CommsDeviceToString(current)) << endl;
            }
        }
        if (m_docking_ports.size() > 0)
        {
            ss << "Docking Ports: " << endl;
            for (auto current : m_docking_ports)
            {
                ss << fmt::format("{}{}", tab, SpaceStation::DockingPortToString(current)) << endl;
            }
        }
        if (m_kerbals.size() > 0)
        {
            ss << "Kerbals Present: " << endl;
            for (auto current : m_kerbals)
            {
                ss << fmt::format("{}{}", tab, current) << endl;
            }
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

    SpaceStationBuilder &SpaceStationBuilder::AddCommsDevice(CommunicationDevice dev)
    {
        m_space_station->m_comms_devices.push_back(dev);
        return *this;
    }

    SpaceStationBuilder &SpaceStationBuilder::AddCommsDevices(size_t quantity, CommunicationDevice dev)
    {
        for (auto i = 0; i < quantity; ++i)
        {
            m_space_station->m_comms_devices.push_back(dev);
        }
        return *this;
    }

    SpaceStationBuilder &SpaceStationBuilder::AddDockingPort(DockingPort port)
    {
        m_space_station->m_docking_ports.push_back(port);
        return *this;
    }

    SpaceStationBuilder &SpaceStationBuilder::AddDockingPorts(size_t quantity, DockingPort port)
    {
        for (auto i = 0; i < quantity; i++)
        {
            m_space_station->m_docking_ports.push_back(port);
        }

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

    string SpaceStation::GetName()
    {
        return m_station_name;
    }

    string SpaceStation::GetStationID()
    {
        return m_station_id;
    }

    size_t SpaceStation::GetCapacity()
    {
        return m_capacity;
    }

    bool SpaceStation::isActive()
    {
        return m_active;
    }

    OrbitalParameters SpaceStation::GetOrbitalDetails()
    {
        return m_orbit_details;
    }

    void to_json(json& j, const SpaceStation& ss)
    {
        j = json{{"id", ss.m_station_id}, {"name", ss.m_station_name},
                {"active", ss.m_active}, {"dockingPorts", ss.m_docking_ports},
                {"capacity", ss.m_capacity}, {"commsDevs", ss.m_comms_devices},
                {"kerbals", ss.m_kerbals}, {"apoapsis", ss.m_orbit_details.apoapsis},
                {"periapsis", ss.m_orbit_details.periapsis}, {"orbiting", ss.m_orbiting_body}};
    
    }

    void to_json(json& j, const std::unique_ptr<SpaceStation>& ss)
    {
        j = json{{"id", ss->m_station_id}, {"name", ss->m_station_name},
                {"active", ss->m_active}, {"dockingPorts", ss->m_docking_ports},
                {"capacity", ss->m_capacity}, {"commsDevs", ss->m_comms_devices},
                {"kerbals", ss->m_kerbals}, {"apoapsis", ss->m_orbit_details.apoapsis},
                {"periapsis", ss->m_orbit_details.periapsis}, {"orbiting", ss->m_orbiting_body}};

    }

    void from_json(const json& j, std::unique_ptr<SpaceStation>& ss)
    {
        ss.reset(new SpaceStation());
        j.at("id").get_to(ss->m_station_id);
        j.at("name").get_to(ss->m_station_name);
        j.at("active").get_to(ss->m_active);
        j.at("dockingPorts").get_to(ss->m_docking_ports);
        j.at("capacity").get_to(ss->m_capacity);
        j.at("commsDevs").get_to(ss->m_comms_devices);
        j.at("apoapsis").get_to(ss->m_orbit_details.apoapsis);
        j.at("periapsis").get_to(ss->m_orbit_details.periapsis);
        j.at("orbiting").get_to(ss->m_orbiting_body);
        j.at("kerbals").get_to(ss->m_kerbals);
    }

    void from_json(const json& j, SpaceStation& ss)
    {
        j.at("id").get_to(ss.m_station_id);
        j.at("name").get_to(ss.m_station_name);
        j.at("active").get_to(ss.m_active);
        j.at("dockingPorts").get_to(ss.m_docking_ports);
        j.at("capacity").get_to(ss.m_capacity);
        j.at("commsDevs").get_to(ss.m_comms_devices);
        j.at("apoapsis").get_to(ss.m_orbit_details.apoapsis);
        j.at("periapsis").get_to(ss.m_orbit_details.periapsis);
        j.at("orbiting").get_to(ss.m_orbiting_body);
        j.at("kerbals").get_to(ss.m_kerbals);
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

    SpaceStationBuilder& SpaceStationBuilder::AddDockingPorts(vector<DockingPort> ports)
    {
        m_space_station->m_docking_ports = ports;
        return *this;
    }

    SpaceStationBuilder& SpaceStationBuilder::AddKerbals(vector<string> kerbals)
    {
        m_space_station->m_kerbals = kerbals;
        return *this;
    }

    SpaceStationBuilder& SpaceStationBuilder::AddCommsDevices(vector<CommunicationDevice> devs)
    {
        m_space_station->m_comms_devices = devs;
        return *this;
    }

    std::unique_ptr<SpaceStation> SpaceStationBuilder::createStationFromConsoleInput()
    {
        bool validInput = false;
        bool doneEnteringList = false;
        string buffer;
        string station_id;
        string station_name;
        vector<DockingPort> docking_ports;
        vector<CommunicationDevice> comms_devs;
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

        std::cout << "Enter Station Apoapsis: ";
        while (!(std::cin >> params.apoapsis))
        {
            std::cout << "Invalid Response. Response must be an integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter Station Apoapsis: ";
        }

        // Clear the input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter Station Periapsis: ";
        while (!(std::cin >> params.periapsis))
        {
            std::cout << "Invalid Response. Response must be an integer" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter Station Periapsis: ";
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "AP: " << params.apoapsis << std::endl;
        std::cout << "PE: " << params.periapsis << std::endl;

        validInput = false;

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
            for(auto i = 0; i < quantity; ++i)
            {
                docking_ports.push_back(selectedDp);
            }


            
        }

        for(auto current : docking_ports)
        {
            std::cout << SpaceStation::DockingPortToString(current) << std::endl;
        }

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

            for(auto i = 0; i < quantity; ++i)
            {
                comms_devs.push_back(selectedDevice);
            }
        }

        for (const auto& current : comms_devs)
        {
            std::cout << SpaceStation::CommsDeviceToString(current) << std::endl;
        }

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
            .AddCommsDevices(comms_devs)
            .AddDockingPorts(docking_ports)
            .AddKerbals(kerbals)
            .build();
        

        return newStation;


    }
}


